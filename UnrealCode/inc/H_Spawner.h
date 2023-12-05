// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "H_Building.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "H_Spawner.generated.h"

UCLASS()
class TPHEXDIO_API AH_Spawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AH_Spawner();

	// Array of materials
	UPROPERTY(EditAnywhere, Category = "Floor materials")
	TArray<UMaterial*> _floorMaterials;

	// Generated string
	UPROPERTY(EditAnywhere, Category = "Building string")
	FString _generatedString;

	// Holds a reference to the H_BP_Building;
	UPROPERTY(EditAnywhere, Category = "Building blueprint")
	TSubclassOf<class AH_Building> _buildingBlueprint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Spawner functions
	void spawnBuilding(FVector pos, FRotator rot);

	// Get the amount of floors from the generated string
	int32 getFloorAmountFromString();

	// Return a material based on index
	UMaterial* getMaterialFromIndex(int32 index);
};
