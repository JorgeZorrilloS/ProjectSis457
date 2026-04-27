// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownMover.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Constructor: configura valores iniciales del Pawn
ATopDownMover::ATopDownMover()
{
    // Permite ejecutar Tick() en cada frame
    PrimaryActorTick.bCanEverTick = true;

    // Posición inicial del actor en el centro del mapa
    FVector centerLocation(0, 0, 0);
    SetActorLocation(centerLocation);

    // No poseer automáticamente el Pawn
    AutoPossessPlayer = EAutoReceiveInput::Disabled;

    // Recibir input del Player 0
    AutoReceiveInput = EAutoReceiveInput::Player0;

    // Crear el componente visual (malla)
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    // Buscar y asignar una malla desde los assets del proyecto
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(
        TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_TriPyramid.Shape_TriPyramid'")
    );

    // Verificar que el asset fue encontrado correctamente
    if (CubeMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(CubeMeshAsset.Object);
    }

    // Valores iniciales de movimiento
    Velocity = 400.0f;
    MoveDirection = EMoveDirection::Right;
    bIsMoving = false;
}


// Se ejecuta al iniciar el juego o al crear el actor
void ATopDownMover::BeginPlay()
{
    Super::BeginPlay();

    // Asegurar posición inicial
    FVector centerLocation(0, 0, 0);
    SetActorLocation(centerLocation);

    // Mostrar mensaje en pantalla
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            5.0f,
            FColor::Yellow,
            FString::Printf(TEXT("Starting the game"))
        );
    }

    // Registrar mensaje en el Output Log
    UE_LOG(LogTemp, Warning, TEXT("Starting the game"));

    // Obtener el PlayerController actual
    APlayerController* PC = GetWorld()->GetFirstPlayerController();

    // Habilitar recepción de input
    if (PC)
    {
        UE_LOG(LogTemp, Warning, TEXT("Input player set up"));
        EnableInput(PC);
    }

    // Asociar la acción de entrada al método ToggleMovement
    if (InputComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("binding fine"));

        InputComponent->BindAction(
            "ToggleMove",
            IE_Pressed,
            this,
            &ATopDownMover::ToggleMovement
        ).bConsumeInput = false;
    }
}


// Se ejecuta en cada frame
void ATopDownMover::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Lógica de movimiento
    if (bIsMoving)
    {
        // Obtener posición actual
        FVector CurrentLocation = GetActorLocation();

        // Vector de movimiento inicial
        FVector MovementStep = FVector::ZeroVector;

        // Determinar dirección según el enum
        switch (MoveDirection)
        {
        case EMoveDirection::Up:
            MovementStep.X = 1.0f;
            break;

        case EMoveDirection::Down:
            MovementStep.X = -1.0f;
            break;

        case EMoveDirection::Right:
            MovementStep.Y = 1.0f;
            break;

        case EMoveDirection::Left:
            MovementStep.Y = -1.0f;
            break;

            // Movimiento diagonal
        case EMoveDirection::UpRight:
            MovementStep.X = 1.0f;
            MovementStep.Y = 1.0f;
            break;

        case EMoveDirection::UpLeft:
            MovementStep.X = 1.0f;
            MovementStep.Y = -1.0f;
            break;

        case EMoveDirection::DownLeft:
            MovementStep.X = -1.0f;
            MovementStep.Y = -1.0f;
            break;

        case EMoveDirection::DownRight:
            MovementStep.X = -1.0f;
            MovementStep.Y = 1.0f;
            break;
        }

        // Normalizar el vector para mantener velocidad constante
        MovementStep = MovementStep.GetSafeNormal();

        // Calcular nueva posición usando DeltaTime (independiente del FPS)
        CurrentLocation += MovementStep * Velocity * DeltaTime;

        // Aplicar nueva posición al actor
        SetActorLocation(CurrentLocation);

        // Normalización adicional (no estrictamente necesaria, pero segura)
        MovementStep = MovementStep.GetSafeNormal();
    }
}


// Configura las entradas del jugador
void ATopDownMover::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UE_LOG(LogTemp, Warning, TEXT("Input player set up"));

    // Asociar la acción de entrada
    PlayerInputComponent->BindAction(
        "ToggleMove",
        IE_Pressed,
        this,
        &ATopDownMover::ToggleMovement
    ).bConsumeInput = false;
}


// Alterna el estado de movimiento
void ATopDownMover::ToggleMovement()
{
    // Cambiar entre mover y detener
    bIsMoving = !bIsMoving;

    // Mostrar estado en pantalla
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            5.0f,
            FColor::Yellow,
            FString::Printf(
                TEXT("Spacebar Pressed! bIsMoving is now: %s"),
                bIsMoving ? TEXT("TRUE") : TEXT("FALSE")
            )
        );
    }

    // Registrar evento en el Output Log
    UE_LOG(LogTemp, Warning, TEXT("Spacebar Action Listened."));
}