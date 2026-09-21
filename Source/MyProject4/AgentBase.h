// AgentBase.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AgentBase.generated.h"

UENUM(BlueprintType)
enum class EDecisionModel : uint8
{
	BT,
	FSM,
	GOAP
};

UCLASS()
class YOURPROJECT_API AAgentBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAgentBase();

	EDecisionModel GetModel() const { return Model; }

	// SceneCapture output for PiP
	class UTextureRenderTarget2D* GetRenderTarget() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Agent") EDecisionModel Model = EDecisionModel::FSM;

	UPROPERTY(VisibleAnywhere, Category="PiP") TObjectPtr<class USceneComponent> PipRoot;
	UPROPERTY(VisibleAnywhere, Category="PiP") TObjectPtr<class USceneCaptureComponent2D> PipCapture;

	// created runtime
	UPROPERTY() TObjectPtr<class UTextureRenderTarget2D> PipRT;

	virtual void BeginPlay() override;

	void CreatePipRenderTargetIfNeeded();
};