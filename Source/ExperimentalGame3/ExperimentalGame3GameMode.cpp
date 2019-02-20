// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ExperimentalGame3GameMode.h"
#include "ExperimentalGame3HUD.h"
#include "ExperimentalGame3Character.h"
#include "UObject/ConstructorHelpers.h"

AExperimentalGame3GameMode::AExperimentalGame3GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AExperimentalGame3HUD::StaticClass();
}
