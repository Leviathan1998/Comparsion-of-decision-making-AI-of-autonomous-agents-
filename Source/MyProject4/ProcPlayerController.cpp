// ProcPlayerController.cpp
#include "ProcPlayerController.h"
#include "ExperimentManager.h"
#include "AgentBase.h"
#include "PipHUDWidget.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"

void AProcPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	// assign in editor to WBP_PipHUD (child of UPipHUDWidget)
	EnsureExperimentAndBindPip();
}

void AProcPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("TogglePip"), IE_Pressed, this, &AProcPlayerController::TogglePip);

	InputComponent->BindAction(TEXT("FocusSpectator"), IE_Pressed, this, &AProcPlayerController::FocusSpectator);
	InputComponent->BindAction(TEXT("FocusBT"), IE_Pressed, this, &AProcPlayerController::FocusBT);
	InputComponent->BindAction(TEXT("FocusFSM"), IE_Pressed, this, &AProcPlayerController::FocusFSM);
	InputComponent->BindAction(TEXT("FocusGOAP"), IE_Pressed, this, &AProcPlayerController::FocusGOAP);
}

void AProcPlayerController::EnsureExperimentAndBindPip()
{
	// find existing ExperimentManager in world; if none, spawn one
	for (TActorIterator<AExperimentManager> It(GetWorld()); It; ++It)
	{
		Experiment = *It;
		break;
	}
	if (!Experiment.IsValid())
	{
		FActorSpawnParameters P;
		P.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Experiment = GetWorld()->SpawnActor<AExperimentManager>(AExperimentManager::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, P);
	}

	// create widget once (hidden by default)
	if (!PipWidget && PipWidgetClass)
	{
		PipWidget = CreateWidget<UPipHUDWidget>(this, PipWidgetClass);
		if (PipWidget)
		{
			PipWidget->AddToViewport(10);
			PipWidget->SetVisibility(ESlateVisibility::Hidden);
			bPipVisible = false;
		}
	}

	// bind textures (agents might spawn in BeginPlay of ExperimentManager, so do a safe pull)
	if (PipWidget && Experiment.IsValid())
	{
		if (AAgentBase* BT = Experiment->GetBT())
			PipWidget->SetBTTexture(BT->GetRenderTarget());
		if (AAgentBase* FSM = Experiment->GetFSM())
			PipWidget->SetFSMTexture(FSM->GetRenderTarget());
		if (AAgentBase* GOAP = Experiment->GetGOAP())
			PipWidget->SetGOAPTexture(GOAP->GetRenderTarget());
	}
}

void AProcPlayerController::TogglePip()
{
	if (!PipWidget)
	{
		EnsureExperimentAndBindPip();
		if (!PipWidget) return;
	}

	bPipVisible = !bPipVisible;
	PipWidget->SetVisibility(bPipVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void AProcPlayerController::ApplyFocus(EFocusTarget Target)
{
	FocusTarget = Target;

	// Spectator pawn
	APawn* SpectatorPawn = GetPawn();

	if (!Experiment.IsValid())
		EnsureExperimentAndBindPip();

	AActor* NewViewTarget = nullptr;

	switch (Target)
	{
		case EFocusTarget::Spectator: NewViewTarget = SpectatorPawn; break;
		case EFocusTarget::BT:        NewViewTarget = Experiment.IsValid() ? Experiment->GetBT()   : nullptr; break;
		case EFocusTarget::FSM:       NewViewTarget = Experiment.IsValid() ? Experiment->GetFSM()  : nullptr; break;
		case EFocusTarget::GOAP:      NewViewTarget = Experiment.IsValid() ? Experiment->GetGOAP() : nullptr; break;
	}

	if (NewViewTarget)
	{
		SetViewTargetWithBlend(NewViewTarget, 0.25f);
	}
}

void AProcPlayerController::FocusSpectator() { ApplyFocus(EFocusTarget::Spectator); }
void AProcPlayerController::FocusBT()        { ApplyFocus(EFocusTarget::BT); }
void AProcPlayerController::FocusFSM()       { ApplyFocus(EFocusTarget::FSM); }
void AProcPlayerController::FocusGOAP()      { ApplyFocus(EFocusTarget::GOAP); }