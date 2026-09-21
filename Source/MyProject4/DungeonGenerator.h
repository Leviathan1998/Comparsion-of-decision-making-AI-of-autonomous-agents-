// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.generated.h"

UENUM(blueprintType)
enum class ECellType : uint8
{
	Empty
	Dead_End
	Corridor
	Corridor_Right
	Trap_Door

};

USTRUCT()
struct FGridCell
{
	GENERATED_BODY()

	UPROPERTY()
	ECellType Type = ECellType::Empty;

	UPROPERTY()
	bool occupied = false;

};

UCLASS()
class MYPROJECT4_API ADungeonGenerator : public AActor
{
	GENERATED_BODY()

public:
	//Sets default values for this actor's properties
		ADungeonGenerator();

protected:
	//Called when the game starts or when spawned
		virtual void BeginPlay() override;

public:
	//Called every frame
		UPROPERTY(EditAnywhere, Category = "Dungeon")
	     int32 GridWidth = 15;

	UPROPERTY(EditAnywhere, Category = "Dungeon")
	int32 GridHeight = 15;

	UPROPERTY(EditAnywhere, Category = "Dungeon")
	float CellSize = 400.0f;

	UPROPERTY(EditAnywhere, Category = "Dungeon")
	int32 MaxCorridorCount = 25;

	UPROPERTY(EditAnywhere, Category = "Dungeon")
	bool bGenerateOnBeginPlay = true;

	UPROPERTY(EditAnywhere, Category = "Dungeon|Meshes")
	UStaticMesh* CorridorMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Dungeon|Meshes")
	UStaticMesh* DeadEndMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Dungeon|Meshes")
	UStaticMesh* TrapDoorMesh = nullptr;

	UFUNCTION(CallInEditor, Category = "Dungeon")
	void GenerateDungeon();

	UFUNCTION(CallInEditor, Category = "Dungeon")
	void ClearDungeon();

private:
	TArray<FGridCell> Grid;

	UPROPERTY()
	TArray<AActor*> SpawnedPieces;

	int32 GetIndex(int32 X, int32 Y) const;
	bool IsInside(int32 X, int32 Y) const;
	bool IsFree(int32 X, int32 Y) const;

	void InitializeGrid();
	void GenerateLayout();
	void SpawnLayout();

	FIntPoint FindStartCell() const;
	TArray<FIntPoint> GetValidNeighbors(const FIntPoint& Cell) const;
	FRotator GetRotationFromDirection(const FIntPoint& From, const FIntPoint& To) const;

	void SpawnPiece(UStaticMesh* Mesh, const FVector& Location, const FRotator& Rotation);


};
