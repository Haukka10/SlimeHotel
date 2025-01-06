// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlimeHotelGameMode.h"
#include "SlimeHotelCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASlimeHotelGameMode::ASlimeHotelGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
