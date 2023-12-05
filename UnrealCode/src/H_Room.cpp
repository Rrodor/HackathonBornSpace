// Fill out your copyright notice in the Description page of Project Settings.

#include "H_Room.h"
#include "H_Spawner.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AH_Room::AH_Room()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AH_Room::BeginPlay()
{
	Super::BeginPlay();

	int idxMaterial = GetActorLocation().Z / 300.0f;

	// Log the material index
	UE_LOG(LogTemp, Warning, TEXT("Material index: %d"), idxMaterial);

	// get the spawner in the scene
	AH_Spawner* spawner = nullptr;
	for (TActorIterator<AH_Spawner> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		spawner = *ActorItr;
		break;
	}

	// get the material from the spawner
	UMaterial* material = spawner->getMaterialFromIndex(idxMaterial);

	// Iterate through all child components
    TArray<UActorComponent*> Components;
    GetComponents(Components);
    for (UActorComponent* Component : Components)
    {
        // Check if the component is a static mesh component
        UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(Component);
        if (MeshComponent)
        {
            MeshComponent->SetMaterial(0, material);
            break; // Break the loop if you only want to set the material for the first found mesh
        }
    }
}

// Called every frame
void AH_Room::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

