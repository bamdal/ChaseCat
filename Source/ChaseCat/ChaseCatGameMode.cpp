// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChaseCatGameMode.h"
#include "ChaseCatCharacter.h"
#include "UObject/ConstructorHelpers.h"

AChaseCatGameMode::AChaseCatGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
