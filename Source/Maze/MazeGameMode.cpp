// Copyright Epic Games, Inc. All Rights Reserved.

#include "MazeGameMode.h"
#include "ExitPortal.h"
#include "Utils/PrefabricatorFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

AMazeGameMode::AMazeGameMode() : Super()
{
    PrimaryActorTick.bCanEverTick = true;
    TotalSecondsMazeCompletion = 0;
}

void AMazeGameMode::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(MazeCompletionTimerHandle, this, &AMazeGameMode::IncrementMazeCompletionTime, 1.0f, true);
    SubscribeToLevelCompleteEvent();
}

void AMazeGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void AMazeGameMode::IncrementMazeCompletionTime()
{
    TotalSecondsMazeCompletion = TotalSecondsMazeCompletion + 1;
}

void AMazeGameMode::LevelComplete()
{
    UE_LOG(LogTemp, Warning, TEXT("LEVEL COMPLETE CALLED"))

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Yellow, FString::Printf(TEXT("Level Complete, seconds since start: %d"), TotalSecondsMazeCompletion));
    }
    GetWorldTimerManager().ClearTimer(MazeCompletionTimerHandle);
    // TODO: load next level
    //
    // if(Levels.Num() > 0) // or something
    // {
    //     UPrefabricatorBlueprintLibrary::SpawnPrefab(GetWorld(), MyPrefab, FTransform(), 0);
    // }

}

void AMazeGameMode::SubscribeToLevelCompleteEvent()
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AExitPortal::StaticClass(), FoundActors);
    if (FoundActors.Num() > 0)
    {
        auto ExitPortal = Cast<AExitPortal>(FoundActors[0]);
        if (ExitPortal)
        {            
            ExitPortal->LevelComplete.AddDynamic(this, &AMazeGameMode::LevelComplete);
        }
    }
}
