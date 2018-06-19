// Copyright 2018 Infinite Replay. All Rights Reserved.

#include "IRGameGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "MainCharacter.h"

AIRGameGameModeBase::AIRGameGameModeBase() : Super()
{
	UE_LOG(LogTemp, Warning, TEXT("GameMode now running"));

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/MainCharacter/Blueprints/MainCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}