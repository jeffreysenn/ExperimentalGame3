// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NervousComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNervousDelegate, int32, NervousIndex);

UENUM(BlueprintType)
enum class ENervousEnum :uint8
{
	NE_Clear, //full control
	NE_Little, //+camera shake
	NE_Medium, //+camera turning
	NE_Heavy, //+invert axis
	NE_Extreme //+running away
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPERIMENTALGAME3_API UNervousComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNervousComponent();

public:

protected:
	UPROPERTY(VisibleAnywhere)
	float NervousPercent = 0;
	ENervousEnum NervousState = ENervousEnum::NE_Clear;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float NPNaturalDecreaseSpeed = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float LittleThreshold = 8;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MediumThreshold = 16;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float HeavyThreshold = 24;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ExtremeThreshold = 32;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ComputeNervousState(float DeltaTime);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void IncreaseNervousPercent(float DeltaPercent);

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetNervousPercent() { return NervousPercent; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ENervousEnum GetNervousState() { return NervousState; }

	UFUNCTION(BlueprintCallable)
	void TryNotFacing(AActor* ActorToAvoid);

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FNervousDelegate OnNervousChanged;
};
