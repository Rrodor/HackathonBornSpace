// Fill out your copyright notice in the Description page of Project Settings.

#include "H_Player.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AH_Player::AH_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = Camera;

	CameraDistanceFromOrigin = 6000.0f;
	YawRotation = 0.0f;
	PitchRotation = 0.0f;
}

// Called when the game starts or when spawned
void AH_Player::BeginPlay()
{
	Super::BeginPlay();

	// Set initial position and orientation
	SetActorLocation(FVector(0.0f, -CameraDistanceFromOrigin, 0.0f));
	SetActorRotation(FRotator(0.0f, YawRotation, 0.0f));

	// Create an iterator that will loop through all actors of type AASpawner in the world
	for (TActorIterator<AH_Spawner> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		_Spawner = *ActorItr;
		break;
	}

	// Log the string
	FString _prompt = "Je veux un batiment de 2 etages";
	GetString(_prompt);
	std::ifstream file("/Users/rhony/Documents/serv/string.txt");
	std::string line;
	std::getline(file, line);

	// log the line
	UE_LOG(LogTemp, Warning, TEXT("line: %s"), *FString(line.c_str()));
}

FString AH_Player::GetString(const FString& Prompt)
{
    ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    if (SocketSubsystem == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("SocketSubsystem not available!"));
        return FString();
    }

    TSharedRef<FInternetAddr> ServerAddr = SocketSubsystem->CreateInternetAddr();
    bool bIsValid;
    ServerAddr->SetIp(TEXT("127.0.0.1"), bIsValid);
    ServerAddr->SetPort(8897);

    if (!bIsValid)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid IP address!"));
        return FString();
    }

    FSocket* Socket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("default"), false);
    if (Socket == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create socket!"));
        return FString();
    }

    if (!Socket->Connect(*ServerAddr))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to connect to the server!"));
        return FString();
    }

    // Convert FString to UTF-8 and send
    FTCHARToUTF8 Convert(*Prompt);
    int32 BytesSent = 0;
    Socket->Send((uint8*)Convert.Get(), Convert.Length(), BytesSent);

    // Wait for 5 seconds
    FPlatformProcess::Sleep(5.0f);

    // Receive data
    TArray<uint8> ReceivedData;
    uint32 Size;
    FString Result;
    while (Socket->HasPendingData(Size))
    {
        ReceivedData.SetNumUninitialized(FMath::Min(Size, 1024u));

        int32 BytesRead = 0;
        if (Socket->Recv(ReceivedData.GetData(), ReceivedData.Num(), BytesRead))
        {
            Result += FString(UTF8_TO_TCHAR(ReceivedData.GetData())).Left(BytesRead);
        }
    }

    Socket->Close();
    ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);

    return Result;
}

/*
std::string AH_Player::getString(std::string prompt)
{
	const char	* server_ip = "127.0.0.1";
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1)
	{
		printf("socket() error\n");
		return 0;
	}
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8897);
	if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) == -1)
	{
		printf("inet_pton() error\n");
		return 0;
	}
	if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
	{
		printf("connect() error\n");
		return 0;
	}
	char buffer[1024];
    ssize_t bytes_received;
	send(client_socket, prompt.c_str(), prompt.length(), 0);
	sleep(5);
	bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
	buffer[bytes_received] = '\0';
	close(client_socket);
	return buffer;
}*/

// Called every frame
void AH_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Interpolate towards the target rotations
	PitchRotation = FMath::FInterpTo(PitchRotation, TargetPitchRotation, DeltaTime, InertiaSpeed);
	YawRotation = FMath::FInterpTo(YawRotation, TargetYawRotation, DeltaTime, InertiaSpeed);

	// Calculate new location based on rotations
	FVector NewLocation;
	NewLocation.X = CameraDistanceFromOrigin * FMath::Sin(FMath::DegreesToRadians(PitchRotation)) * FMath::Cos(FMath::DegreesToRadians(YawRotation));
	NewLocation.Y = CameraDistanceFromOrigin * FMath::Sin(FMath::DegreesToRadians(PitchRotation)) * FMath::Sin(FMath::DegreesToRadians(YawRotation));
	NewLocation.Z = CameraDistanceFromOrigin * FMath::Cos(FMath::DegreesToRadians(PitchRotation));

	SetActorLocation(NewLocation);

	// Always look at the origin
	FVector LookAtTarget = FVector(0.0f, 0.0f, 400.0f);
	FRotator NewRotation = (LookAtTarget - NewLocation).Rotation();
	SetActorRotation(NewRotation);
}

// Called to bind functionality to input
void AH_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "action" bindings.
	PlayerInputComponent->BindAction("SpawnAction", IE_Pressed, this, &AH_Player::HandleSpawnInput);
	PlayerInputComponent->BindAxis("LookHorizontal", this, &AH_Player::HandleMouseMovementHorizontal);
	PlayerInputComponent->BindAxis("LookVertical", this, &AH_Player::HandleMouseMovementVertical);
	PlayerInputComponent->BindAction("LeftMouseButtonDown", IE_Pressed, this, &AH_Player::OnLeftMouseButtonDown);
	PlayerInputComponent->BindAction("LeftMouseButtonDown", IE_Released, this, &AH_Player::OnLeftMouseButtonUp);
}

void AH_Player::OnLeftMouseButtonDown()
{
	bIsLeftMouseButtonDown = true;
}

void AH_Player::OnLeftMouseButtonUp()
{
	bIsLeftMouseButtonDown = false;
}

void AH_Player::HandleMouseMovementVertical(float Delta)
{
	if (bIsLeftMouseButtonDown)
		TargetPitchRotation = FMath::Clamp(TargetPitchRotation + Delta, MinPitch, MaxPitch);
}

void AH_Player::HandleMouseMovementHorizontal(float Delta)
{
	if (bIsLeftMouseButtonDown)
		TargetYawRotation += Delta;
}

void AH_Player::HandleSpawnInput()
{
	UE_LOG(LogTemp, Warning, TEXT("HandleSpawnInput called"));
	if (_Spawner)
	{
		spawn();
		UE_LOG(LogTemp, Warning, TEXT("spawner called"));
	}
}

void AH_Player::spawn()
{
	UE_LOG(LogTemp, Warning, TEXT("spawn building called"));

	// Spawn a new actor at the player's location
	FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	_Spawner->spawnBuilding(SpawnLocation, SpawnRotation);
}
