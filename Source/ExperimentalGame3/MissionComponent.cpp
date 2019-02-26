// Fill out your copyright notice in the Description page of Project Settings.

#include "MissionComponent.h"
#include "InteractiveProp.h"

// Sets default values for this component's properties
UMissionComponent::UMissionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MissionTexts.Add("Mission 0");
}


// Called when the game starts
void UMissionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (CurrentMissionIndex < TargetProps.Num())
	{
		if (TargetProps[CurrentMissionIndex])
		{
			TargetProps[CurrentMissionIndex]->SetActivateProp(true);
		}
	}
	
}


// Called every frame
void UMissionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMissionComponent::NextMission()
{
	if (CurrentMissionIndex + 1 < MissionTexts.Num())
	{
		CurrentMissionIndex += 1;
		if (CurrentMissionIndex < TargetProps.Num())
		{
			if (TargetProps[CurrentMissionIndex])
			{
				TargetProps[CurrentMissionIndex]->SetActivateProp(true);
			}
		}
	}
	else
	{
		OnMissionCompleted.Broadcast();
	}
}

