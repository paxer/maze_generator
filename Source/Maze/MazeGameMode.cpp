// Copyright Epic Games, Inc. All Rights Reserved.

#include "MazeGameMode.h"
#include "MazeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMazeGameMode::AMazeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
