// Copyright Epic Games, Inc. All Rights Reserved.

#include "GQ_3DShootingGameMode.h"
#include "GQ_3DShootingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGQ_3DShootingGameMode::AGQ_3DShootingGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
