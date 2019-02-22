// Fill out your copyright notice in the Description page of Project Settings.

#include "NervousComponent.h"

// Sets default values for this component's properties
UNervousComponent::UNervousComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNervousComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



// Called every frame
void UNervousComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ComputeNervousState(DeltaTime);
}

void UNervousComponent::ComputeNervousState(float DeltaTime)
{
	IncreaseNervousPercent(NPNaturalIncreaseSpeed * DeltaTime);

	switch (NervousState)
	{
	case ENervousEnum::NE_Clear:
		if (NervousPercent > LittleThreshold)
		{
			//NervousPercent = MediumThreshold;
			NervousState = ENervousEnum::NE_Little;
		}
		break;
	case ENervousEnum::NE_Little:
		if (NervousPercent > MediumThreshold)
		{
			//NervousPercent = HeavyThreshold;
			NervousState = ENervousEnum::NE_Medium;
		}
		else if(NervousPercent <= LittleThreshold)
		{
			NervousState = ENervousEnum::NE_Clear;
		}
		break;
	case ENervousEnum::NE_Medium:
		if (NervousPercent > HeavyThreshold)
		{
			//NervousPercent = ExtremeThreshold;
			NervousState = ENervousEnum::NE_Heavy;
		}
		else if (NervousPercent <= MediumThreshold)
		{
			NervousState = ENervousEnum::NE_Little;
		}
		break;
	case ENervousEnum::NE_Heavy:
		if (NervousPercent > ExtremeThreshold)
		{
			//NervousPercent = 100;
			NervousState = ENervousEnum::NE_Extreme;
		}
		else if (NervousPercent <= HeavyThreshold)
		{
			NervousState = ENervousEnum::NE_Heavy;
		}
		break;
	case ENervousEnum::NE_Extreme:
		if (NervousPercent <= ExtremeThreshold)
		{
			NervousState = ENervousEnum::NE_Heavy;
		}
		break;
	default:
		break;
	}
}

void UNervousComponent::IncreaseNervousPercent(float DeltaPercent)
{
	float NextNervousPercent = NervousPercent + DeltaPercent;
	if (NervousPercent > 100)
	{
		NervousPercent = 100;
	}
	else if (NextNervousPercent < 0)
	{
		NextNervousPercent = 0;
	}
	else
	{
		NervousPercent = NextNervousPercent;
	}
}

void UNervousComponent::TryNotFacing(AActor * ActorToAvoid)
{
}
