// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FPSpheresGameMode.h"
#include "FPSpheresHUD.h"
#include "FPSpheresCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPSpheresGameMode::AFPSpheresGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSpheresHUD::StaticClass();
}
