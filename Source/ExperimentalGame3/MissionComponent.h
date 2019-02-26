// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MissionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMissionDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXPERIMENTALGAME3_API UMissionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMissionComponent();

public:
	UPROPERTY(BlueprintAssignable)
	FMissionDelegate OnMissionCompleted;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> MissionTexts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AInteractiveProp*> TargetProps;

	int32 CurrentMissionIndex = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void NextMission();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetCurrentMissionText() { return MissionTexts[CurrentMissionIndex]; }
};
