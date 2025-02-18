// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGenerator.h"
#include "Wall.h"

const int MazeSizeMax = 101;

// Sets default values
AMazeGenerator::AMazeGenerator()
{    
    PrimaryActorTick.bCanEverTick = true;
    SizeX = 5;
    SizeY = 5;
    RegenerateMaze = false;
}

void AMazeGenerator::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
    Super::PostEditChangeProperty(e);    
    FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
    if (PropertyName == GET_MEMBER_NAME_CHECKED(AMazeGenerator, RegenerateMaze))
    {
        RegenerateMaze = false;
        GenerateMaze(SizeX, SizeY);        
    }    
}

// Called when the game starts or when spawned
void AMazeGenerator::BeginPlay()
{
    Super::BeginPlay();
    GenerateMaze(SizeX, SizeY);
}

// Called every frame
void AMazeGenerator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void AMazeGenerator::GenerateMaze(const int TileX, const int TileY)
{
    // only odd numbers allowed
    if (TileX % 2 == 0 || TileY % 2 == 0)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Only odd numbers allowed for Maze size X and Y!"));   
        }
        return;
    }
    
    if (Ground == nullptr || Wall == nullptr)
    {
        return;
    }

    float CaptureX = 0.0f;
    float CaptureY = 0.0f;
    const float Offset = 350.0f;


    // Destroy already spawned PlayerStart and ExitPortal if spawned in editor
    if(SpawnedPlayerStart != nullptr)
    {
        SpawnedPlayerStart->Destroy();
    }
    if(SpawnedExitPortal != nullptr)
    {
        SpawnedExitPortal->Destroy();
    }

    //Init Maze
    MazeGrid.Clear();    
    MazeGrid.AddUninitialized(TileX, TileY);

    // this builds outer walls and the initial symmetric grid structure filled with walls separated equally by ground blocks
    for (int x = 0; x < TileX; x++)
    {
        for (int y = 0; y < TileY; y++)
        {
            const FVector Location(CaptureX, CaptureY, 0.0f);
            if (y == 0 || x == 0 || y == TileY - 1 || x == TileX - 1 || y % 2 == 0 && x % 2 == 0)
            {
                
                MazeGrid.Rows[x].Columns[y] = SpawnBlock(Wall, Location);
            }
            else
            {
                MazeGrid.Rows[x].Columns[y] = SpawnBlock(Ground, Location);;
            }

            // spawn PlayerStart
            if (CaptureX == Offset && CaptureY == Offset)
            {
                const auto CenterBlockLocation = FVector(Location.X + (Offset / 2), Location.Y + (Offset / 2), Location.Z + (Offset / 2));                 
                SpawnedPlayerStart = SpawnBlock(PlayerStart, CenterBlockLocation);
            }

            // spawn ExitPortal
            if (y == TileY - 1 && x == TileX - 1)
            {
                const auto CenterBlockLocation = FVector(Location.X - (Offset / 2), Location.Y - (Offset / 2), Location.Z + (Offset / 2)); 
                SpawnedExitPortal = SpawnBlock(ExitPortal, CenterBlockLocation);                
            }

            CaptureY += Offset;
            if (CaptureY >= Offset * TileY) { CaptureY = 0; }
        }
        CaptureX += Offset;
        if (CaptureX >= Offset * TileX) { CaptureX = 0; }
    }
    
    //this adds walls to the existing grid to form random corridors

    for (int y = 2; y < TileY - 1; y += 2)
    {
        int Dx = 2;
        int Dy = y;
        //int rnd4;
    
        switch (rand() % 4)
        {
        case 0: Dx++;
            break;
        case 1: Dx--;
            break;
        case 2: Dy++;
            break;
        case 3: Dy--;
            break;
        default: break;
        }
    
        if (!MazeGrid.Rows[Dx].Columns[Dy]->IsA(AWall::StaticClass()))
        {
            ReplaceBlock(Wall, Dx, Dy);
        }
        else
        {
            y -= 2;
        }
    }
    for (int x = 4; x < TileX - 1; x += 2)
    {
        for (int y = 2; y < TileY - 1; y += 2)
        {
            int Dx = x;
            int Dy = y;            
    
            switch (rand() % 3)
            {
            case 0: Dy++;
                break;
            case 1: Dy--;
                break;
            case 2: Dx++;
                break;
            default: break;
            }
    
            if (!MazeGrid.Rows[Dx].Columns[Dy]->IsA(AWall::StaticClass()))
            {
                ReplaceBlock(Wall, Dx, Dy);
            }
            else
            {
                y -= 2;
            }
        }
    }
}

AActor* AMazeGenerator::SpawnBlock(UClass* BlockType, const FVector Location, const FRotator Rotation)
{
    if(BlockType == nullptr)
    {
        return nullptr;
    }
    AActor* NewBlock = GetWorld()->SpawnActor<AActor>(BlockType, Location, Rotation);
    #if WITH_EDITOR
        NewBlock->SetFolderPath("/Maze");
    #endif
    return NewBlock;
}


void AMazeGenerator::ReplaceBlock(UClass* NewBlock, const int MazeX, const int MazeY)
{
    auto BlockToDestroy = MazeGrid.Rows[MazeX].Columns[MazeY];
    if(BlockToDestroy != nullptr)
    {
        FVector Location = BlockToDestroy->GetActorLocation();
        BlockToDestroy->Destroy();
        MazeGrid.Rows[MazeX].Columns[MazeY] = SpawnBlock(NewBlock, Location);;
    }
}
