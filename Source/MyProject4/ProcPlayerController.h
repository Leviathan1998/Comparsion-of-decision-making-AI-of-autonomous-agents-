// ProcPlayerController.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProcPlayerController.generated.h"

UENUM()
enum class EFocusTarget : uint8
{
	Spectator,
	BT,
	FSM,
	GOAP
};

UCLASS()
class YOURPROJECT_API AProcPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="UI") TSubclassOf<class UPipHUDWidget> PipWidgetClass;
	UPROPERTY() TObjectPtr<class UPipHUDWidget> PipWidget;

	UPROPERTY() TWeakObjectPtr<class AExperimentManager> Experiment;

	bool bPipVisible = false;
	EFocusTarget FocusTarget = EFocusTarget::Spectator;

	void TogglePip();
	void FocusSpectator();
	void FocusBT();
	void FocusFSM();
	void FocusGOAP();

	void ApplyFocus(EFocusTarget Target);
	void EnsureExperimentAndBindPip();
};