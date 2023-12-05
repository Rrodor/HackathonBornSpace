// Fill out your copyright notice in the Description page of Project Settings.

#include "H_Spawner.h"

// Sets default values
AH_Spawner::AH_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AH_Spawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AH_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AH_Spawner::spawnBuilding(FVector pos, FRotator rot)
{
	AActor* bld = nullptr;

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

		// spawns an instance of an AH_Building
		bld = world->SpawnActor<AActor>(_buildingBlueprint, pos, rot, spawnParams);
	}
}

int32 AH_Spawner::getFloorAmountFromString()
{
	int32 floorAmount = 0;
	int32 stringLength = _generatedString.Len();

	for (int32 i = 0; i < stringLength; i++)
	{
		if (_generatedString[i] == 'F')
		{
			floorAmount++;
		}
	}
	return floorAmount;
}

UMaterial* AH_Spawner::getMaterialFromIndex(int32 idx)
{
	UMaterial* tmpMaterial = nullptr;

	if (idx < _floorMaterials.Num())
	{
		tmpMaterial = _floorMaterials[idx];
	}

	return tmpMaterial;
}
