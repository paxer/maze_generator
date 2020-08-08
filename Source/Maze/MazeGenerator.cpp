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
    if (Ground == nullptr)
    {
        return;
    }

    float CaptureX = 0.0f;
    float CaptureY = 0.0f;
    float offset = 400.0f;
    float iter = 0;
    int tileID = 0;
    int RandomEndTileLoc = rand() % ((int)tileX - 1) + 1;

    //Init Maze
    MazeGrid.Clear();
    MazeGrid.AddUninitialized(tileX, tileY);

    for (int x = 0; x < tileX; x++)
    {
        for (int y = 0; y < tileY; y++)
        {
            if (y == 0 || x == 0 || y == tileY - 1 || x == tileX - 1 || y % 2 == 0 && x % 2 == 0)
            {
                const FVector GenSpawnLoc(CaptureX, CaptureY, 0.0f);
                const FRotator GenSpawnRot(0.0f, 0.0f, 0.0f);
                AActor* WallActor = GetWorld()->SpawnActor<AActor>(Wall, GenSpawnLoc, GenSpawnRot);
                #if WITH_EDITOR
                  WallActor->SetFolderPath("/Maze");
                #endif
                MazeGrid.Rows[x].Columns[y] = WallActor;
            }
            else
            {
                const FVector GenSpawnLoc(CaptureX, CaptureY, 0.0f);
                const FRotator GenSpawnRot(0.0f, 0.0f, 0.0f);
                AActor* GroundActor = GetWorld()->SpawnActor<AActor>(Ground, GenSpawnLoc, GenSpawnRot);
                #if WITH_EDITOR
                  GroundActor->SetFolderPath("/Maze");
                #endif
                MazeGrid.Rows[x].Columns[y] = GroundActor; //GroundTile;
            }
            //-------------Starting Tile Spawn---------------
            if (CaptureX == offset && CaptureY == offset)
            {
                MazeGrid.Rows[1].Columns[1]->Destroy();

                const FVector GenSpawnLoc(offset, offset, 0.0f);
                const FRotator GenSpawnRot(0.0f, 0.0f, 0.0f);
                //Tile Start
                AActor* StartTile = GetWorld()->SpawnActor<AActor>(TileStartBP, GenSpawnLoc, GenSpawnRot);
                #if WITH_EDITOR
                  StartTile->SetFolderPath("/Maze");
                #endif
                MazeGrid.Rows[1].Columns[1] = StartTile;
            }
            //-------------Ending Tile Spawn---------------
            if (y == tileY - 1 && x == tileX - 1)
            {
                MazeGrid.Rows[x - 1].Columns[y - 1]->Destroy();

                const FVector GenSpawnLoc(((tileX - 2) * offset), ((tileY - 2) * offset), 0);
                const FRotator GenSpawnRot(0.0f, 0.0f, 0.0f);
                // Tile End
                AActor* EndTile = GetWorld()->SpawnActor<AActor>(TileEndBP, GenSpawnLoc, GenSpawnRot);
                MazeGrid.Rows[x - 1].Columns[y - 1] = EndTile;
            }
            CaptureY += offset;
            if (CaptureY >= offset * tileY) { CaptureY = 0; }
        }
        CaptureX += offset;
        if (CaptureX >= offset * tileX) { CaptureX = 0; }
    }
    //-----------------------------------------------This adds walls to the existing grid to form corridors----------------------------------------------------------

    for (int y = 2; y < tileY - 1; y += 2)
    {
        int dx = 2;
        int dy = y;
        int rnd4;

        switch (rnd4 = rand() % 4)
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
        //if (MazeGrid.Rows[dx].Columns[dy]->GetActorLabel() != "Wall")
        if(!MazeGrid.Rows[dx].Columns[dy]->IsA(AWall::StaticClass()))
        {
            FVector f = MazeGrid.Rows[dx].Columns[dy]->GetActorLocation();
            MazeGrid.Rows[dx].Columns[dy]->Destroy();

            const FVector GenSpawnLoc(f);
            const FRotator GenSpawnRot(0.0f, 0.0f, 0.0f);

            AActor* BlockTile = GetWorld()->SpawnActor<AActor>(Wall, GenSpawnLoc, GenSpawnRot);
            #if WITH_EDITOR
              BlockTile->SetFolderPath("/Maze");
            #endif
            MazeGrid.Rows[dx].Columns[dy] = BlockTile;
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
            int rnd3;

            switch (rnd3 = rand() % 3)
            {
            case 0: dy++;
                break;
            case 1: dy--;
                break;
            case 2: dx++;
                break;
            }
            //if (bd.getPixel(dx, dy) != Status.WALL) {
            //if (MazeGrid.Rows[dx].Columns[dy]->GetActorLabel() != "Wall")
            if(!MazeGrid.Rows[dx].Columns[dy]->IsA(AWall::StaticClass()))
            {
                FVector f = MazeGrid.Rows[dx].Columns[dy]->GetActorLocation();
                MazeGrid.Rows[dx].Columns[dy]->Destroy();

                const FVector GenSpawnLoc(f);
                const FRotator GenSpawnRot(0.0f, 0.0f, 0.0f);

                AActor* BlockTile = GetWorld()->SpawnActor<AActor>(Wall, GenSpawnLoc, GenSpawnRot);
                #if WITH_EDITOR
                                BlockTile->SetFolderPath("/Maze");
                #endif
                MazeGrid.Rows[dx].Columns[dy] = BlockTile;
            }
            else
            {
                y -= 2;
            }
        }
    }
}
