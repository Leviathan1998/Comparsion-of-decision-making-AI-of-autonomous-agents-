// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGenerator.h"

// Sets default values
ADungeonGenerator::ADungeonGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADungeonGenerator::BeginPlay()
{
	Super::BeginPlay();

	if (bGenerateOnBeginPlay)
	{
		GenerateDungeon();
	}
	
}

// Called every frame
int32 ADungeonGenerator::GetIndex(int32 X, int32 Y) const
{
	return Y * GridWidth + X;
}

bool ADungeonGenerator::IsInside(int32 X, int32 Y) const
{
	return X >= 0 && X < GridWidth && Y >= 0 && Y < GridHeight;
}

bool ADungeonGenerator::IsFree(int32 X, int32 Y) const
{
	return IsInside(X, Y) && !Grid[GetIndex(X, Y)].bOccupied;
}

void ADungeonGenerator::InitializeGrid()
{
	Grid.Empty();
	Grid.SetNum(GridWidth * GridHeight);

	for (FGridCell& Cell : Grid)
	{
		Cell.Type = ECellType::Empty;
		Cell.bOccupied = false;
	}
}

FIntPoint ADungeonGenerator::FindStartCell() const
{
	return FIntPoint(GridWidth / 2, GridHeight / 2);
}

TArray<FIntPoint> ADungeonGenerator::GetValidNeighbors(const FIntPoint& Cell) const
{
	TArray<FIntPoint> Neighbors;

	const TArray<FIntPoint> Directions = {
		FIntPoint(1, 0),
		FIntPoint(-1, 0),
		FIntPoint(0, 1),
		FIntPoint(0, -1)
	};

	for (const FIntPoint& Dir : Directions)
	{
		const int32 NX = Cell.X + Dir.X;
		const int32 NY = Cell.Y + Dir.Y;

		if (IsFree(NX, NY))
		{
			Neighbors.Add(FIntPoint(NX, NY));
		}
	}

	return Neighbors;
}

FRotator ADungeonGenerator::GetRotationFromDirection(const FIntPoint& From, const FIntPoint& To) const
{
	const FIntPoint Delta = To - From;

	if (Delta.X != 0)
	{
		return FRotator(0.f, 0.f, 0.f);
	}

	if (Delta.Y != 0)
	{
		return FRotator(0.f, 90.f, 0.f);
	}

	return FRotator::ZeroRotator;
}

void ADungeonGenerator::GenerateLayout()
{
	TArray<FIntPoint> Stack;

	const FIntPoint Start = FindStartCell();
	Grid[GetIndex(Start.X, Start.Y)].bOccupied = true;
	Grid[GetIndex(Start.X, Start.Y)].Type = ECellType::Corridor;
	Stack.Push(Start);

	int32 CorridorCount = 1;
	TArray<FIntPoint> LeafCells;

	while (Stack.Num() > 0 && CorridorCount < MaxCorridorCount)
	{
		const FIntPoint Current = Stack.Last();
		TArray<FIntPoint> Neighbors = GetValidNeighbors(Current);

		if (Neighbors.Num() > 0)
		{
			const int32 RandomIndex = FMath::RandRange(0, Neighbors.Num() - 1);
			const FIntPoint Next = Neighbors[RandomIndex];

			Grid[GetIndex(Next.X, Next.Y)].bOccupied = true;
			Grid[GetIndex(Next.X, Next.Y)].Type = ECellType::Corridor;

			Stack.Push(Next);
			CorridorCount++;
		}
		else
		{
			LeafCells.Add(Current);
			Stack.Pop();
		}
	}

	if (LeafCells.Num() > 0)
	{
		const FIntPoint TrapCell = LeafCells.Last();

		for (const FIntPoint& Leaf : LeafCells)
		{
			Grid[GetIndex(Leaf.X, Leaf.Y)].Type = ECellType::DeadEnd;
		}

		Grid[GetIndex(TrapCell.X, TrapCell.Y)].Type = ECellType::TrapDoor;
	}
}

void ADungeonGenerator::SpawnPiece(UStaticMesh* Mesh, const FVector& Location, const FRotator& Rotation)
{
	if (!Mesh)
	{
		return;
	}

	AStaticMeshActor* Spawned = GetWorld()->SpawnActor<AStaticMeshActor>(Location, Rotation);
	if (!Spawned)
	{
		return;
	}

	Spawned->GetStaticMeshComponent()->SetStaticMesh(Mesh);
	Spawned->SetActorMobility(EComponentMobility::Static);
	SpawnedPieces.Add(Spawned);
}

void ADungeonGenerator::SpawnLayout()
{
	const FVector Origin = GetActorLocation();

	for (int32 Y = 0; Y < GridHeight; Y++)
	{
		for (int32 X = 0; X < GridWidth; X++)
		{
			const FGridCell& Cell = Grid[GetIndex(X, Y)];
			if (!Cell.bOccupied)
			{
				continue;
			}

			const FVector Location = Origin + FVector(X * CellSize, Y * CellSize, 0.f);
			FRotator Rotation = FRotator::ZeroRotator;

			UStaticMesh* MeshToSpawn = nullptr;

			switch (Cell.Type)
			{
			case ECellType::Corridor:
				MeshToSpawn = CorridorMesh;
				break;
			case ECellType::DeadEnd:
				MeshToSpawn = DeadEndMesh;
				break;
			case ECellType::TrapDoor:
				MeshToSpawn = TrapDoorMesh;
				break;
			default:
				break;
			}

			SpawnPiece(MeshToSpawn, Location, Rotation);
		}
	}
}

void ADungeonGenerator::ClearDungeon()
{
	for (AActor* Actor : SpawnedPieces)
	{
		if (IsValid(Actor))
		{
			Actor->Destroy();
		}
	}

	SpawnedPieces.Empty();
}

void ADungeonGenerator::GenerateDungeon()
{
	ClearDungeon();
	InitializeGrid();
	GenerateLayout();
	SpawnLayout();
}
}

