// Fill out your copyright notice in the Description page of Project Settings.

#include "H_Building.h"
#include "H_Spawner.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AH_Building::AH_Building()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AH_Building::BeginPlay()
{
	Super::BeginPlay();
	spawnFloor(GetActorLocation(), GetActorRotation());
}

void AH_Building::spawnFloor(FVector pos, FRotator rot)
{
	AActor* flr = nullptr;

	UE_LOG(LogTemp, Warning, TEXT("spawnBuilding called"));
	// log position
	UE_LOG(LogTemp, Warning, TEXT("pos: %s"), *pos.ToString());
	// log rotation
	UE_LOG(LogTemp, Warning, TEXT("rot: %s"), *rot.ToString());

	UWorld* world = GetWorld();
	if (world)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		int32 totalFloor = 0;
		// Create an iterator that will loop through all actors of type AASpawner in the world
		for (TActorIterator<AH_Spawner> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			totalFloor = (*ActorItr)->getFloorAmountFromString();
			break;
		}
		for (int i = 0; i < totalFloor; i++)
		{
			FRotator newRot = FRotator(0, 0, 0);
			FVector newPos = FVector(0.0f, 0.0f, 300.0f * i);
			flr = world->SpawnActor<AActor>(_floorBlueprint, newPos, newRot, spawnParams);
		}
	}
}

// Called every frame
void AH_Building::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

