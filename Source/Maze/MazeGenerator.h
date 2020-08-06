// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MazeHUD)
    bool RunInConstructor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MazeHUD)
    bool ShowTests;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MazeGen101isMax)
    float MazeXKeepODD;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MazeGen101isMax)
    float MazeYKeepODD;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MazeTiles)
    UClass* Wall;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MazeTiles)
    TSubclassOf<AActor> Ground;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MazeTiles)
    UClass* TileGroundBP;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MazeTiles)
    UClass* TileBlockBP;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MazeTiles)
    UClass* TilePillarBP;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MazeTiles)
    UClass* TileStartBP;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MazeTiles)
    UClass* TileEndBP;
    
    UFUNCTION(BlueprintCallable, Category = MazeGen)
    void GenMaze(float tileX, float tileY);

    UPROPERTY()
    FMazeGrid JoyMazeGrid;
    
    virtual void PostInitializeComponents() override;
    
    // Sets default values for this actor's properties
    AMazeGenerator();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
};

template <typename AMazeGen>
FORCEINLINE AMazeGen* SpawnBP(
    UWorld* TheWorld,
    UClass* TheBP,
    const FVector& Loc,
    const FRotator& Rot,
    const bool bNoFail = true,
    AActor* Owner = NULL,
    APawn* Instigator = NULL
    ){
    if (!TheWorld) return NULL;
    if (!TheBP) return NULL;
    //~~~~~~~~~~~


    FActorSpawnParameters SpawnInfo;
    SpawnInfo.bNoFail = bNoFail;
    SpawnInfo.Owner = Owner;
    SpawnInfo.Instigator = Instigator;
    SpawnInfo.bDeferConstruction = false;


    return TheWorld->SpawnActor<AMazeGen>(TheBP, Loc, Rot, SpawnInfo);
}
