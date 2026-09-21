// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject4GameMode.h"
#include "MyProject4PlayerController.h"
#include "MyProject4Character.h"
#include "UObject/ConstructorHelpers.h"

AMyProject4GameMode::AMyProject4GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMyProject4PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}