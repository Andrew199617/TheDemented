// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "TheDemented.h"
#include "TheDementedGameMode.h"
#include "TheDementedHUD.h"
#include "TheDementedCharacter.h"

ATheDementedGameMode::ATheDementedGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATheDementedHUD::StaticClass();
}
