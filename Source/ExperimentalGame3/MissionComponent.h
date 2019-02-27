// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MissionComponent.generated.h"

USTRUCT(BlueprintType)
struct FMissionDetail
{
	GENERATED_BODY();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
	FString MissionString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
	class AInteractiveProp* PropToClick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
	class USoundBase* SoundToPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
	class AActor* SoundOwningActor;


public:
	FMissionDetail()
	{
		MissionString = FString();
		PropToClick = nullptr;
		SoundToPlay = nullptr;
		SoundOwningActor = nullptr;
	}

};

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
	TArray<FMissionDetail> Missions;

	int32 CurrentMissionIndex = -1;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void NextMission();

	UFUNCTION(BlueprintPure)
	FString GetCurrentMissionText() const;
};
