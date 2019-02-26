// Fill out your copyright notice in the Description page of Project Settings.

#include "TimerComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UTimerComponent::UTimerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTimerComponent::BeginPlay()
{
	Super::BeginPlay();

	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;

	//Binding the function with specific variables
	TimerDel.BindUFunction(this, FName("IncreaseCurrentTime"), TimeScale);
	GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, TimerTickRate, true);
	
}

void UTimerComponent::IncreaseCurrentTime(float DeltaTime)
{
	if (!bIsActive) { return; }
	CurrentTime = (CurrentTime + DeltaTime < MaxTime) ? CurrentTime + DeltaTime : MaxTime;
}


// Called every frame
void UTimerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTimerComponent::SetTimerActive(bool NewActive)
{
	bIsActive = NewActive;
}

