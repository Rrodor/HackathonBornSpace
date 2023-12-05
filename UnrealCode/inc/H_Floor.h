// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "H_Room.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "H_Floor.generated.h"

UCLASS()
class TPHEXDIO_API AH_Floor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AH_Floor();

	// Holds a reference to the H_BP_Room
	UPROPERTY(EditAnywhere, Category = "Room blueprint")
	TSubclassOf<class AH_Room> _roomBlueprint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void spawnRoom(FVector pos, FRotator rot);

};
