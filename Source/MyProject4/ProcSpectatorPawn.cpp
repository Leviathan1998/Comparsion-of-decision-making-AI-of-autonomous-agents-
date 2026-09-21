// ProcSpectatorPawn.cpp
#include "ProcSpectatorPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AProcSpectatorPawn::AProcSpectatorPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 4000.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(-65.f, 0.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;
}

void AProcSpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AProcSpectatorPawn::InputMoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AProcSpectatorPawn::InputMoveRight);
	PlayerInputComponent->BindAxis(TEXT("Zoom"), this, &AProcSpectatorPawn::InputZoom);
}

void AProcSpectatorPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// pan
	if (!FMath::IsNearlyZero(MoveForward) || !FMath::IsNearlyZero(MoveRight))
	{
		const FVector Forward = FVector::ForwardVector;
		const FVector Right = FVector::RightVector;
		const FVector Delta = (Forward * MoveForward + Right * MoveRight) * PanSpeed * DeltaSeconds;
		AddActorWorldOffset(Delta, true);
	}

	// zoom
	if (!FMath::IsNearlyZero(ZoomInput))
	{
		const float NewLen = FMath::Clamp(SpringArm->TargetArmLength - ZoomInput * ZoomSpeed * DeltaSeconds, MinArmLength, MaxArmLength);
		SpringArm->TargetArmLength = NewLen;
		ZoomInput = 0.f;
	}
}

void AProcSpectatorPawn::InputMoveForward(float Value) { MoveForward = Value; }
void AProcSpectatorPawn::InputMoveRight(float Value) { MoveRight = Value; }
void AProcSpectatorPawn::InputZoom(float Value) { ZoomInput = Value; }