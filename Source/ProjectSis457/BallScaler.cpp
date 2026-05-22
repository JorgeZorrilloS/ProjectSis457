#include "BallScaler.h"

#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"

#include "GameFramework/PlayerController.h"

#include "Engine/Engine.h"

#include "InputCoreTypes.h"

#include "UObject/ConstructorHelpers.h"


// Constructor
ABallScaler::ABallScaler()
{
    // Activar Tick
    PrimaryActorTick.bCanEverTick = true;

    // Crear componente visual
    MeshComponent =
        CreateDefaultSubobject<UStaticMeshComponent>(
            TEXT("MeshComponent")
        );

    RootComponent = MeshComponent;

    // Buscar esfera por defecto
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
        SphereMeshAsset(
            TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'")
        );

    // Asignar mesh
    if (SphereMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(
            SphereMeshAsset.Object
        );
    }

    // =========================
    // MOVEMENT
    // =========================

    MovementSpeed = 300.0f;

    MovementDirection = FVector::ZeroVector;

    bIsMoving = true;

    // =========================
    // SCALING
    // =========================

    ScaleRate = FVector(0.5f, 0.5f, 0.5f);

    bIsScaling = false;
}


// BeginPlay
void ABallScaler::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("BallScaler iniciado correctamente")
    );

    // Obtener PlayerController
    APlayerController* PC =
        GetWorld()->GetFirstPlayerController();

    if (PC)
    {
        // Activar input
        EnableInput(PC);

        // Mostrar cursor
        PC->bShowMouseCursor = true;

        // Eventos del mouse
        PC->bEnableClickEvents = true;
        PC->bEnableMouseOverEvents = true;

        // =====================================
        // CREAR INPUT COMPONENT MANUALMENTE
        // =====================================

        InputComponent = NewObject<UInputComponent>(
            this,
            TEXT("InputComponent")
        );

        InputComponent->RegisterComponent();

        InputComponent->bBlockInput = false;

        // =====================================
        // BINDINGS
        // =====================================

        InputComponent->BindAction(
            "ToggleMove",
            IE_Pressed,
            this,
            &ABallScaler::ToggleMovement
        );

        InputComponent->BindAction(
            "ToggleScale",
            IE_Pressed,
            this,
            &ABallScaler::ToggleScaling
        );

        InputComponent->BindAction(
            "MoveUp",
            IE_Pressed,
            this,
            &ABallScaler::MoveUp
        );

        InputComponent->BindAction(
            "MoveDown",
            IE_Pressed,
            this,
            &ABallScaler::MoveDown
        );

        InputComponent->BindAction(
            "MoveLeft",
            IE_Pressed,
            this,
            &ABallScaler::MoveLeft
        );

        InputComponent->BindAction(
            "MoveRight",
            IE_Pressed,
            this,
            &ABallScaler::MoveRight
        );

        // Agregar al stack de input
        EnableInput(PC);

        // =====================================
        // CLICK EVENT
        // =====================================

        if (MeshComponent)
        {
            MeshComponent->OnClicked.AddDynamic(
                this,
                &ABallScaler::OnObjectClicked
            );
        }

        UE_LOG(
            LogTemp,
            Warning,
            TEXT("INPUTS CONFIGURADOS")
        );
    }
}


// Tick
void ABallScaler::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // =========================
    // MOVEMENT
    // =========================

    if (bIsMoving)
    {
        FVector CurrentLocation =
            GetActorLocation();

        CurrentLocation +=
            MovementDirection *
            MovementSpeed *
            DeltaTime;

        SetActorLocation(CurrentLocation);
    }

    // =========================
    // SCALING
    // =========================

    if (bIsScaling)
    {
        FVector CurrentScale =
            GetActorScale3D();

        CurrentScale +=
            ScaleRate * DeltaTime;

        SetActorScale3D(CurrentScale);
    }
}


// =========================
// DIRECTIONS
// =========================

void ABallScaler::MoveUp()
{
    MovementDirection = FVector(1, 0, 0);

    UE_LOG(LogTemp, Warning, TEXT("Direccion: Arriba"));
}

void ABallScaler::MoveDown()
{
    MovementDirection = FVector(-1, 0, 0);

    UE_LOG(LogTemp, Warning, TEXT("Direccion: Abajo"));
}

void ABallScaler::MoveLeft()
{
    MovementDirection = FVector(0, -1, 0);

    UE_LOG(LogTemp, Warning, TEXT("Direccion: Izquierda"));
}

void ABallScaler::MoveRight()
{
    MovementDirection = FVector(0, 1, 0);

    UE_LOG(LogTemp, Warning, TEXT("Direccion: Derecha"));
}


// =========================
// TOGGLE MOVEMENT
// =========================

void ABallScaler::ToggleMovement()
{
    bIsMoving = !bIsMoving;

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Movimiento cambiado")
    );

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            2.0f,
            FColor::Yellow,
            FString::Printf(
                TEXT("bIsMoving: %s"),
                bIsMoving
                ? TEXT("TRUE")
                : TEXT("FALSE")
            )
        );
    }
}


// =========================
// TOGGLE SCALING
// =========================

void ABallScaler::ToggleScaling()
{
    bIsScaling = !bIsScaling;

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Scaling cambiado")
    );

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            2.0f,
            FColor::Cyan,
            FString::Printf(
                TEXT("bIsScaling: %s"),
                bIsScaling
                ? TEXT("TRUE")
                : TEXT("FALSE")
            )
        );
    }
}


// =========================
// CLICK EVENT
// =========================

void ABallScaler::OnObjectClicked(
    UPrimitiveComponent* TouchedComponent,
    FKey ButtonPressed
)
{
    // Click izquierdo
    if (ButtonPressed == EKeys::LeftMouseButton)
    {
        // Aumentar velocidad
        MovementSpeed += 100.0f;

        UE_LOG(
            LogTemp,
            Warning,
            TEXT("Velocidad aumentada")
        );

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1,
                2.0f,
                FColor::Green,
                FString::Printf(
                    TEXT("Velocidad actual: %.2f"),
                    MovementSpeed
                )
            );
        }
    }

    // Click derecho
    if (ButtonPressed == EKeys::RightMouseButton)
    {
        ToggleScaling();

        UE_LOG(
            LogTemp,
            Warning,
            TEXT("Click derecho detectado")
        );
    }
}