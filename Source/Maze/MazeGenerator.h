// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.generated.h"

USTRUCT()
struct FMazeGridRow
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY()
    TArray<AActor*> Columns;

    void AddNewColumn()
    {
        Columns.Add(NULL);
    }

    //default properties
    FMazeGridRow()
    {
    }
};

USTRUCT()
struct FMazeGrid
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY()
    TArray<FMazeGridRow> Rows;

    void AddNewRow()
    {
        Rows.Add(FMazeGridRow());
    }

    void AddUninitialized(const int32 RowCount, const int32 ColCount)
    {
        //Add Rows
        for (int32 r = 0; r < RowCount; r++)
        {
            AddNewRow();
        }

        //Add Columns
        for (int32 r = 0; r < RowCount; r++)
        {
            for (int32 c = 0; c < ColCount; c++)
            {
                Rows[r].AddNewColumn();
            }
        }
    }

    void Clear()
    {
        if (Rows.Num() <= 0) return;
        //~~~~~~~~~~~~~~~

        //Destroy any walls
        const int32 RowTotal = Rows.Num();
        const int32 ColTotal = Rows[0].Columns.Num();

        for (int32 r = 0; r < RowTotal; r++)
        {
            for (int32 c = 0; c < ColTotal; c++)
            {
                if (Rows[r].Columns[c] && Rows[r].Columns[c]->IsValidLowLevel())
                {
                    Rows[r].Columns[c]->Destroy();
                }
            }
        }

        //Empty
        for (int32 v = 0; v < Rows.Num(); v++)
        {
            Rows[v].Columns.Empty();
        }
        Rows.Empty();
    }

    //default properties
    FMazeGrid()
    {
    }
};


UCLASS()
class MAZE_API AMazeGenerator : public AActor
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze Properites")
    bool RegenerateMaze;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze Properites")
    int SizeX;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maze Properites")
    int SizeY;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Maze Properites")
    TSubclassOf<AActor> Wall;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Maze Properites")
    TSubclassOf<AActor> Ground;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Maze Properites")
    TSubclassOf<AActor> ExitPortal;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Maze Properites")
    TSubclassOf<AActor> PlayerStart;

    UFUNCTION(BlueprintCallable, Category = MazeGen)
    void GenerateMaze(int TileX, int TileY);

    UPROPERTY()
    FMazeGrid MazeGrid;

    // Sets default values for this actor's properties
    AMazeGenerator();

    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

 private:

    AActor* SpawnedPlayerStart;
    AActor* SpawnedExitPortal;
    
    void ReplaceBlock(UClass* NewBlock, int MazeX, int MazeY);
    AActor* SpawnBlock(UClass* BlockType, FVector Location, FRotator Rotation = FRotator(0,0,0));
};
