// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPERIMENTALGAME3_API UTimerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimerComponent();


protected:
	UPROPERTY(EditAnywhere)
	float MaxTime = 60;

	UPROPERTY(EditAnywhere)
	float TimeScale = 1;

	UPROPERTY(EditAnywhere)
	float TimerTickRate = 1;

	bool bIsActive = true;

private:
	float CurrentTime = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void IncreaseCurrentTime(float DeltaTime);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetTimerPercent() { return CurrentTime / MaxTime; }

	UFUNCTION(BlueprintCallable)
	void SetTimerActive(bool NewActive);
};
