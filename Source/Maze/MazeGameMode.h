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

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;    

private:
    FTimerHandle MazeCompletionTimerHandle;

    int32 TotalSecondsMazeCompletion;

    void IncrementMazeCompletionTime();
};
