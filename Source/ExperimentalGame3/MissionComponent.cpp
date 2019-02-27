// Fill out your copyright notice in the Description page of Project Settings.

#include "MissionComponent.h"
#include "InteractiveProp.h"
#include "Components/SpotLightComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMissionComponent::UMissionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Missions.Add(FMissionDetail());
}


// Called when the game starts
void UMissionComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UMissionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMissionComponent::NextMission()
{
	if (CurrentMissionIndex + 1 < Missions.Num())
	{
		CurrentMissionIndex += 1;

		if (Missions[CurrentMissionIndex].PropToClick)
		{
			Missions[CurrentMissionIndex].PropToClick->SetActivateProp(true);
			auto Comp = Missions[CurrentMissionIndex].PropToClick->GetComponentByClass(USpotLightComponent::StaticClass());
			if (Comp)
			{
				auto SpotLight = Cast<USpotLightComponent>(Comp);
				if (SpotLight)
				{
					SpotLight->SetVisibility(true);
				}
			}

			if (Missions[CurrentMissionIndex].SoundToPlay && Missions[CurrentMissionIndex].SoundOwningActor)
			{
				UGameplayStatics::PlaySoundAtLocation
				(
					this,
					Missions[CurrentMissionIndex].SoundToPlay,
					Missions[CurrentMissionIndex].SoundOwningActor->GetActorLocation()
					//float VolumeMultiplier,
					//float PitchMultiplier,
					//float StartTime,
					//class USoundAttenuation * AttenuationSettings,
					//USoundConcurrency * ConcurrencySettings
				);
			}
		}

	}
	else
	{
		OnMissionCompleted.Broadcast();
	}
}

FString UMissionComponent::GetCurrentMissionText() const
{
	if (CurrentMissionIndex < 0) { return FString(); }

	return Missions[CurrentMissionIndex].MissionString;
}

