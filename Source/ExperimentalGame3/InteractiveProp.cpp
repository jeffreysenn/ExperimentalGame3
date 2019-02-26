// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractiveProp.h"
#include "NervousComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ExperimentalGame3Character.h"

// Sets default values
AInteractiveProp::AInteractiveProp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractiveProp::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerNervousComp = Cast<UNervousComponent>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetComponentByClass(UNervousComponent::StaticClass()));
}

void AInteractiveProp::NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit)
{
}

// Called every frame
void AInteractiveProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

