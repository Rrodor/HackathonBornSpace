// Fill out your copyright notice in the Description page of Project Settings.


#include "H_Gizmo.h"

// Sets default values
AH_Gizmo::AH_Gizmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AH_Gizmo::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AH_Gizmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AH_Gizmo::MoveGizmo(FVector NewLocation)
{
	SetActorLocation(NewLocation);
}
