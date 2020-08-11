// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitPortal.h"
#include "Components/BoxComponent.h"

// Sets default values
AExitPortal::AExitPortal()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    auto OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    OverlapComp->SetBoxExtent(FVector(75, 75, 50));
    RootComponent = OverlapComp;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Mesh->SetupAttachment(RootComponent);

    OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AExitPortal::OnPortalBeginOverlap);
}

// Called when the game starts or when spawned
void AExitPortal::BeginPlay()
{
    Super::BeginPlay();
}

void AExitPortal::OnPortalBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    LevelComplete.Broadcast();
}

// Called every frame
void AExitPortal::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
