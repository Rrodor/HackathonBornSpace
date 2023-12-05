// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <fstream>

#include "Sockets.h"
#include "SocketSubsystem.h"
#include "IPAddress.h"

#include "H_Spawner.h"
#include "H_Gizmo.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "H_Player.generated.h"

UCLASS()
class TPHEXDIO_API AH_Player : public ACharacter
{
	GENERATED_BODY()

private:
	float TargetYawRotation = 0.0f;
	float TargetPitchRotation = 0.0f;
	const float InertiaSpeed = 5.0f;
	const float MaxPitch = 89.0f;
	const float MinPitch = 0.0f;

public:
	// Sets default values for this character's properties
	AH_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void HandleMouseMovementHorizontal(float DeltaX);
	void HandleMouseMovementVertical(float DeltaY);
	void OnLeftMouseButtonDown();
	void OnLeftMouseButtonUp();

	bool bIsLeftMouseButtonDown = false;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Holds a reference to H_Spawner
	AH_Spawner* _Spawner;

	// Function bound to the input
	void HandleSpawnInput();

	// Spawns a building blueprint
	void spawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;

	float CameraDistanceFromOrigin;

	FVector2D LastMousePosition;

	FString GetString(const FString& Prompt);

	float YawRotation;
	float PitchRotation;
};
