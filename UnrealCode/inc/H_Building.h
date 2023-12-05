// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "H_Floor.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "H_Building.generated.h"

UCLASS()
class TPHEXDIO_API AH_Building : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AH_Building();

	// How many floors in the buildings
	int32 _floors = 0;

	// Holds a reference to the H_BP_Floor
	UPROPERTY(EditAnywhere, Category = "Floor blueprint")
	TSubclassOf<class AH_Floor> _floorBlueprint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void spawnFloor(FVector pos, FRotator rot);

};
