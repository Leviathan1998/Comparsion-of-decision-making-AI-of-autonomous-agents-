// ProcSpectatorPawn.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "ProcSpectatorPawn.generated.h"

UCLASS()
class YOURPROJECT_API AProcSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	AProcSpectatorPawn();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(VisibleAnywhere) TObjectPtr<class USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere) TObjectPtr<class UCameraComponent> Camera;

	// movement
	float MoveForward = 0.f;
	float MoveRight = 0.f;

	// zoom
	float ZoomInput = 0.f;

	UPROPERTY(EditAnywhere, Category="TopDown") float PanSpeed = 2000.f;
	UPROPERTY(EditAnywhere, Category="TopDown") float ZoomSpeed = 2500.f;
	UPROPERTY(EditAnywhere, Category="TopDown") float MinArmLength = 1200.f;
	UPROPERTY(EditAnywhere, Category="TopDown") float MaxArmLength = 8000.f;

	void InputMoveForward(float Value);
	void InputMoveRight(float Value);
	void InputZoom(float Value);
};