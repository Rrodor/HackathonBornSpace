// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "H_Gizmo.generated.h"

UCLASS()
class TPHEXDIO_API AH_Gizmo : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AH_Gizmo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveGizmo(FVector NewLocation);

};
