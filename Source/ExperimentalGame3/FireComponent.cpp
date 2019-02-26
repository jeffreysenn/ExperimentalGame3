// Fill out your copyright notice in the Description page of Project Settings.

#include "FireComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InteractiveProp.h"
#include "Components/PrimitiveComponent.h"


// Sets default values for this component's properties
UFireComponent::UFireComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFireComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UFireComponent::GetLookDirection(FVector & LookDirection, FVector & CameraWorldLocation)
{
	int32 ViewportSizeX, ViewportSizeY;
	GetWorld()->GetFirstPlayerController()->GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX / 2, ViewportSizeY / 2);

	return GetWorld()->GetFirstPlayerController()->DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}


// Called every frame
void UFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsAimingCorrect())
	{
		if (InteractiveProp)
		{
			
		}
	}
}

void UFireComponent::Fire()
{
	if (IsAimingCorrect())
	{
		OnFireExecuted.Broadcast(true);
		InteractiveProp->Destroy();
	}
	else
	{
		OnFireExecuted.Broadcast(false);
		if (InteractiveProp)
		{
			auto HitComponent = OutHit->GetComponent();
			if (HitComponent)
			{
				FVector HitDirection = -OutHit->ImpactNormal;
				HitComponent->AddForce(HitDirection*ForceAmount);
			}
		}
	}
}

bool UFireComponent::IsAimingCorrect()
{
	bool bIsAmingCorrect = false;
	InteractiveProp = nullptr;

	FVector LookDirection;
	FVector CameraWorldLocation;
	// "De-project" the screen position of the crosshair to a world direction
	if (GetLookDirection(LookDirection, CameraWorldLocation))
	{
		FCollisionQueryParams Params;
		FCollisionResponseParams  ResponseParam;
		if (GetWorld()->LineTraceSingleByChannel(*OutHit, CameraWorldLocation, CameraWorldLocation + LookDirection * 9999999, ECollisionChannel::ECC_Visibility, Params, ResponseParam))
		{
			InteractiveProp = Cast<AInteractiveProp>(OutHit->GetActor());
			if (InteractiveProp)
			{
				bIsAmingCorrect = InteractiveProp->bShouldHit;
			}
		}
	}
	return bIsAmingCorrect;
}

