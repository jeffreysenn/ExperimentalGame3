// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FireComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFireDelegate, bool, bCorrect);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPERIMENTALGAME3_API UFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFireComponent();

public:
	UPROPERTY(BlueprintAssignable)
	FFireDelegate OnFireExecuted;

	UPROPERTY(EditDefaultsOnly)
	float ForceAmount = 200000;

protected:
	bool bCanCollect = false;


	struct FHitResult* OutHit = new struct FHitResult;
	class AInteractiveProp* InteractiveProp = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool GetLookDirection(FVector &LookDirection, FVector &CameraWorldLocation);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	bool IsAimingCorrect();
};
