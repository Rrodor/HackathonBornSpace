// Fill out your copyright notice in the Description page of Project Settings.


#include "H_Floor.h"

// Sets default values
AH_Floor::AH_Floor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AH_Floor::BeginPlay()
{
	Super::BeginPlay();
	spawnRoom(GetActorLocation(), GetActorRotation());
}

// Called every frame
void AH_Floor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AH_Floor::spawnRoom(FVector pos, FRotator rot)
{
	AActor* rm = nullptr;

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

		// spawns 3 instances of an AH_Room
		for (int i = 0; i < 3; i++)
		{
			FRotator newRot = FRotator(0, 90 * i, 0);
			rm = world->SpawnActor<AActor>(_roomBlueprint, pos, newRot, spawnParams);
		}
	}
}
