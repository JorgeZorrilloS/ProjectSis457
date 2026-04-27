#include "Enemy2.h"
#include "PointerActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"


// Constructor
AEnemy2::AEnemy2()
{
    // Activar Tick para actualizar el movimiento cada frame
    PrimaryActorTick.bCanEverTick = true;

    // Crear la malla del enemigo
    EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
    RootComponent = EnemyMesh;

    // Asignar una malla básica por defecto
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ConeAsset(
        TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'")
    );

    if (ConeAsset.Succeeded())
    {
        EnemyMesh->SetStaticMesh(ConeAsset.Object);
    }

    // Valores iniciales
    MovementSpeed = 300.0f;
}


// Se ejecuta al iniciar el juego
void AEnemy2::BeginPlay()
{
    Super::BeginPlay();
}


// Se ejecuta en cada frame
void AEnemy2::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Si existen puntos de patrulla
    if (PatrolPoints.Num() > 0)
    {
        GoTo(PatrolPoints[CurrentPointIndex], DeltaTime);
    }
}


// Función encargada de mover el enemigo hacia un punto
void AEnemy2::GoTo(APointerActor* Target, float DeltaTime)
{
    // Verificar que el punto sea válido
    if (Target == nullptr) return;

    FVector CurrentLocation = GetActorLocation();
    FVector TargetLocation = Target->GetActorLocation();

    // Si el enemigo llegó al punto
    if (FVector::Dist(CurrentLocation, TargetLocation) <= 5.0f)
    {
        // Avanzar al siguiente punto (patrulla en bucle)
        CurrentPointIndex =
            (CurrentPointIndex + 1) % PatrolPoints.Num();

        // Cambiar la forma del enemigo
        if (Meshes.Num() > 0)
        {
            int32 MeshIndex =
                CurrentPointIndex % Meshes.Num();

            EnemyMesh->SetStaticMesh(
                Meshes[MeshIndex]
            );
        }
    }
    else
    {
        // Mover el enemigo hacia el punto
        FVector Direction =
            (TargetLocation - CurrentLocation).GetSafeNormal();

        FVector NewLocation =
            CurrentLocation +
            (Direction * MovementSpeed * DeltaTime);

        SetActorLocation(NewLocation);
    }
}