// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"

#include "Wall.h"


const int MazeSizeMax = 101;

// Sets default values
AMazeGenerator::AMazeGenerator()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    MazeXKeepODD = 5; //MazeSizeMax;
    MazeYKeepODD = 5; //MazeSizeMax;
}

// Called when the game starts or when spawned
void AMazeGenerator::BeginPlay()
{
    Super::BeginPlay();
    GenerateMaze(MazeXKeepODD, MazeYKeepODD);
}

// Called every frame
void AMazeGenerator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void AMazeGenerator::GenerateMaze(float tileX, float tileY)
{
    if (Ground == nullptr || Wall == nullptr)
    {
        return;
    }

    float CaptureX = 0.0f;
    float CaptureY = 0.0f;
    float offset = 400.0f;
    float ZOffset = -200.0f;

    //Init Maze
    MazeGrid.Clear();
    MazeGrid.AddUninitialized(tileX, tileY);

    // this builds outer walls and the initial symmetric grid structure filled with walls separated equally by ground blocks
    for (int x = 0; x < tileX; x++)
    {
        for (int y = 0; y < tileY; y++)
        {
            if (y == 0 || x == 0 || y == tileY - 1 || x == tileX - 1 || y % 2 == 0 && x % 2 == 0)
            {
                const FVector Location(CaptureX, CaptureY, 0.0f);
                MazeGrid.Rows[x].Columns[y] = SpawnBlock(Wall, Location);
            }
            else
            {
                const FVector Location(CaptureX, CaptureY, ZOffset);
                MazeGrid.Rows[x].Columns[y] = SpawnBlock(Ground, Location);;
            }
            
            if (CaptureX == offset && CaptureY == offset)
            {
                MazeGrid.Rows[1].Columns[1]->Destroy();
                const FVector Location(offset, offset, ZOffset);
                MazeGrid.Rows[1].Columns[1] = SpawnBlock(TileStartBP, Location);;
            }
            
            if (y == tileY - 1 && x == tileX - 1)
            {
                const auto Location = MazeGrid.Rows[x - 1].Columns[y - 1]->GetActorLocation();
                MazeGrid.Rows[x - 1].Columns[y - 1]->Destroy();
                MazeGrid.Rows[x - 1].Columns[y - 1] = SpawnBlock(TileEndBP, Location);;
            }
            CaptureY += offset;
            if (CaptureY >= offset * tileY) { CaptureY = 0; }
        }
        CaptureX += offset;
        if (CaptureX >= offset * tileX) { CaptureX = 0; }
    }
    
    //this adds walls to the existing grid to form random corridors

    for (int y = 2; y < tileY - 1; y += 2)
    {
        int dx = 2;
        int dy = y;
        //int rnd4;
    
        switch (rand() % 4)
        {
        case 0: dx++;
            break;
        case 1: dx--;
            break;
        case 2: dy++;
            break;
        case 3: dy--;
            break;
        }
    
        if (!MazeGrid.Rows[dx].Columns[dy]->IsA(AWall::StaticClass()))
        {
            FVector Location = MazeGrid.Rows[dx].Columns[dy]->GetActorLocation();
            Location.Z = 0;
            MazeGrid.Rows[dx].Columns[dy]->Destroy();
            MazeGrid.Rows[dx].Columns[dy] = SpawnBlock(Wall, Location);;
        }
        else
        {
            y -= 2;
        }
    }
    for (int x = 4; x < tileX - 1; x += 2)
    {
        for (int y = 2; y < tileY - 1; y += 2)
        {
            int dx = x;
            int dy = y;            
    
            switch (rand() % 3)
            {
            case 0: dy++;
                break;
            case 1: dy--;
                break;
            case 2: dx++;
                break;
            }
    
            if (!MazeGrid.Rows[dx].Columns[dy]->IsA(AWall::StaticClass()))
            {
                FVector Location = MazeGrid.Rows[dx].Columns[dy]->GetActorLocation();
                Location.Z = 0;
                MazeGrid.Rows[dx].Columns[dy]->Destroy();
                MazeGrid.Rows[dx].Columns[dy] = SpawnBlock(Wall, Location);;
            }
            else
            {
                y -= 2;
            }
        }
    }
}

AActor* AMazeGenerator::SpawnBlock(UClass* BlockType, FVector Location, FRotator Rotation)
{
    AActor* NewBlock = GetWorld()->SpawnActor<AActor>(BlockType, Location, Rotation);
    #if WITH_EDITOR
        NewBlock->SetFolderPath("/Maze");
    #endif
    return NewBlock;
}
