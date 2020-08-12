// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MazeGameMode.generated.h"

UCLASS(minimalapi)
class AMazeGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMazeGameMode();

    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditDefaultsOnly, Category=Levels)
    TArray<TSubclassOf<AActor>> Levels;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;    

private:

    bool bIsGameplayMap; //  means we load levels from the Levels array
	
    AActor* CurrentLevel;
    
    FTimerHandle MazeCompletionTimerHandle;

    int32 TotalSecondsMazeCompletion;

    int32 CurrentLevelIndex;

    void IncrementMazeCompletionTime();

    UFUNCTION()
    void LevelComplete();

    void SubscribeToLevelCompleteEvent();

    void FindPlayerStartPosition();

	
};
