// AgentBase.cpp
#include "AgentBase.h"
#include "Components/SceneComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/SceneCaptureComponent2D.h"

AAgentBase::AAgentBase()
{
	PrimaryActorTick.bCanEverTick = true;

	PipRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PipRoot"));
	PipRoot->SetupAttachment(GetRootComponent());
	PipRoot->SetRelativeLocation(FVector(0,0,220.f));

	PipCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("PipCapture"));
	PipCapture->SetupAttachment(PipRoot);
	PipCapture->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));
	PipCapture->SetRelativeLocation(FVector(-350.f, 0.f, 140.f));
	PipCapture->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
	PipCapture->bCaptureEveryFrame = true;
	PipCapture->bCaptureOnMovement = true;
	PipCapture->bEnableClipPlane = false;
}

void AAgentBase::BeginPlay()
{
	Super::BeginPlay();
	CreatePipRenderTargetIfNeeded();
}

void AAgentBase::CreatePipRenderTargetIfNeeded()
{
	if (PipRT) return;

	PipRT = NewObject<UTextureRenderTarget2D>(this);
	check(PipRT);

	// 512/1024 podľa výkonu
	PipRT->InitAutoFormat(512, 512);
	PipRT->ClearColor = FLinearColor::Black;
	PipRT->UpdateResourceImmediate(true);

	PipCapture->TextureTarget = PipRT;
}

UTextureRenderTarget2D* AAgentBase::GetRenderTarget() const
{
	return PipRT;
}