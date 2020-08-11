// Copyright Epic Games, Inc. All Rights Reserved.

#include "MazeGameMode.h"

AMazeGameMode::AMazeGameMode() : Super()
{
    PrimaryActorTick.bCanEverTick = true;
    TotalSecondsMazeCompletion = 0;
}

void AMazeGameMode::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(MazeCompletionTimerHandle, this, &AMazeGameMode::IncrementMazeCompletionTime, 1.0f, true);
}

void AMazeGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void AMazeGameMode::IncrementMazeCompletionTime()
{
    TotalSecondsMazeCompletion = TotalSecondsMazeCompletion + 1;

    // if(GEngine)
    // {
    //     GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Seconds since start: %d"), TotalSecondsMazeCompletion));
    // }
}
