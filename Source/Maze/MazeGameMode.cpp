// Copyright Epic Games, Inc. All Rights Reserved.

#include "MazeGameMode.h"
#include "ExitPortal.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

AMazeGameMode::AMazeGameMode() : Super()
{
    PrimaryActorTick.bCanEverTick = true;
    TotalSecondsMazeCompletion = 0;
    CurrentLevelIndex = 0;
    bIsGameplayMap = false;
}

void AMazeGameMode::BeginPlay()
{
    Super::BeginPlay();

    auto LevelName = GetWorld()->GetMapName();
    LevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

    if (LevelName.Contains("TestLoadLevels"))
    {
        bIsGameplayMap = true;
    }


    GetWorldTimerManager().SetTimer(MazeCompletionTimerHandle, this, &AMazeGameMode::IncrementMazeCompletionTime, 1.0f, true);
    //SubscribeToLevelCompleteEvent();

    if (bIsGameplayMap)
    {
        if (Levels.Num() > 0)
        {
            if (Levels[CurrentLevelIndex])
            {
                auto Location = FVector(0, 0, 0);
                auto Rotation = FRotator(0, 0, 0);
                CurrentLevel = GetWorld()->SpawnActor<AActor>(Levels[CurrentLevelIndex], Location, Rotation);

                // TODO: refactor it to multiple methods
                for (auto ChildActor : CurrentLevel->GetComponents())
                {
                    const auto ChildActorComponent = Cast<UChildActorComponent>(ChildActor);
                    if (ChildActorComponent)
                    {
                        const auto PlayerStart = Cast<APlayerStart>(ChildActorComponent->GetChildActor());
                        if (PlayerStart)
                        {
                            auto MyCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();
                            MyCharacter->SetActorTransform(PlayerStart->GetActorTransform());
                        }

                        auto ExitPortal = Cast<AExitPortal>(ChildActorComponent->GetChildActor());
                        if (ExitPortal)
                        {
                            ExitPortal->LevelComplete.AddDynamic(this, &AMazeGameMode::LevelComplete);
                        }
                    }
                }
            }
        }

        //FindPlayerStartPosition();    	
    }
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
    if (CurrentLevel)
    {
        CurrentLevel->Destroy();
    }

    // TODO: load next level
    //
    // Find current level (actually the current level should be taken from the array like Levels[CurrentLevelIndex]


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
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("NO EXIT PORTAL!!!!!"))
    }
}

void AMazeGameMode::FindPlayerStartPosition()
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
    if (FoundActors.Num() > 0)
    {
        auto PlayerStart = Cast<APlayerStart>(FoundActors[0]);
        if (PlayerStart)
        {
            //ExitPortal->LevelComplete.AddDynamic(this, &AMazeGameMode::LevelComplete);
            UE_LOG(LogTemp, Warning, TEXT("WE FOUND PLAYER START!!!!!"))
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("WE NOT FOUND PLAYER START!!!!!"))
    }
}
