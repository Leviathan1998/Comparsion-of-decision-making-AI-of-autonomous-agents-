// ProcGameMode.cpp
#include "ProcGameMode.h"
#include "ProcPlayerController.h"
#include "ProcSpectatorPawn.h"

AProcGameMode::AProcGameMode()
{
	PlayerControllerClass = AProcPlayerController::StaticClass();
	DefaultPawnClass = AProcSpectatorPawn::StaticClass();
}