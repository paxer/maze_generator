// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitPortal.h"

// Sets default values
AExitPortal::AExitPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMesh>(TEXT("Mesh"));	

}

// Called when the game starts or when spawned
void AExitPortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExitPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

