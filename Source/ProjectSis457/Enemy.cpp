#include "Enemy.h"
#include "PointerActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Constructor
AEnemy::AEnemy()
{
    // Activar Tick para actualizar el movimiento en cada frame
    PrimaryActorTick.bCanEverTick = true;

    // Crear la malla del enemigo
    EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
    RootComponent = EnemyMesh;

    // Asignar una malla básica por defecto (cono)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ConeAsset(
        TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'")
    );

    if (ConeAsset.Succeeded())
    {
        EnemyMesh->SetStaticMesh(ConeAsset.Object);
    }

    // Valores iniciales
    MovementSpeed = 300.0f;
    TargetPoint = nullptr;
    AcceptanceRadius = 50.0f;
    CurrentMeshIndex = 0;
}

void AEnemy::BeginPlay()
{
    Super::BeginPlay();
}

void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Si no hay punto objetivo, no hacer nada
    if (TargetPoint == nullptr)
        return;

    FVector CurrentLocation = GetActorLocation();
    FVector TargetLocation = TargetPoint->GetActorLocation();

    float Distance = FVector::Dist(CurrentLocation, TargetLocation);

    // Si el enemigo llegó al punto
    if (Distance <= AcceptanceRadius)
    {
        // Cambiar al siguiente punto
        if (TargetPoint->NextPoint != nullptr)
        {
            TargetPoint = TargetPoint->NextPoint;
        }

        // Cambiar la forma del enemigo
        if (Meshes.Num() > 0)
        {
            CurrentMeshIndex++;

            // Reiniciar índice si se supera el límite
            if (CurrentMeshIndex >= Meshes.Num())
            {
                CurrentMeshIndex = 0;
            }

            if (Meshes.IsValidIndex(CurrentMeshIndex))
            {
                EnemyMesh->SetStaticMesh(
                    Meshes[CurrentMeshIndex]
                );
            }
        }
    }
    else
    {
        // Mover el enemigo hacia el objetivo
        FVector Direction =
            (TargetLocation - CurrentLocation)
            .GetSafeNormal();

        FVector NewLocation =
            CurrentLocation +
            Direction * MovementSpeed * DeltaTime;

        SetActorLocation(NewLocation);
    }
}