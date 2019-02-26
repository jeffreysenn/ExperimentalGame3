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
	NE_Extreme, //+running away
	NE_Lost
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPERIMENTALGAME3_API UNervousComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNervousComponent();

public:
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FNervousDelegate OnNervousChanged;

protected:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float NPNaturalIncreaseSpeed = 1;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float LittleThreshold = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float MediumThreshold = 40;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float HeavyThreshold = 60;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float ExtremeThreshold = 80;

	UPROPERTY(VisibleAnywhere)
	float NervousPercent = 0;

	ENervousEnum NervousState = ENervousEnum::NE_Clear;

	bool bIsActive = true;

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
	FORCEINLINE float GetNervousPercent() const { return NervousPercent; } 

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ENervousEnum GetNervousState() const { return NervousState; } 

	UFUNCTION(BlueprintCallable)
	void SetNervousActive(bool NewActive);
};
