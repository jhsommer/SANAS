// Copyright Epic Games, Inc. All Rights Reserved.

#include "SANASGameMode.h"
#include "Characters/Player/SANAS_PController.h"
#include "GF/SANAS_GameState.h"
#include "UObject/ConstructorHelpers.h"

ASANASGameMode::ASANASGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AController> PlayerControllerBPClass(TEXT("/Game/Player/BP_PlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	
	GameStateClass = ASANAS_GameState::StaticClass();
}
