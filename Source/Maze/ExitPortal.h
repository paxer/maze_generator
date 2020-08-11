// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExitPortal.generated.h"

UCLASS()
class MAZE_API AExitPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExitPortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// TODO: make it box OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	UPROPERTY(EditDefaultsOnly, Category=Components)
	UStaticMeshComponent* Mesh;

	UFUNCTION()
	void OnPortalBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
