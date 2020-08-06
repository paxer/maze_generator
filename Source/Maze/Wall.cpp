// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	 //OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	//OverlapComp->SetBoxExtent(FVector(75, 75, 50));
	//RootComponent = OverlapComp;

	auto SceneRoot = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = SceneRoot;

	//MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	//MeshComp->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Mesh->SetRelativeLocation(FVector(200, 200,0));
	Mesh->SetRelativeScale3D(FVector(4,4,4));
	
	//Mesh->SetWorldLocation(FVector(200, 200,0));
	//Mesh->SetWorldScale3D(FVector(4,4,4));
	Mesh->SetupAttachment(RootComponent);
	

	// SetActorLocation(FVector(200, 200,0));
	// SetActorScale3D(FVector(4,4,4));

}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

