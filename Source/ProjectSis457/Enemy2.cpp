#include "Enemy2.h"
#include "PointerActor.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "UObject/ConstructorHelpers.h"


// Constructor
AEnemy2::AEnemy2()
{
    PrimaryActorTick.bCanEverTick = true;

    // Crear mesh
    EnemyMesh =
        CreateDefaultSubobject<UStaticMeshComponent>(
            TEXT("EnemyMesh")
        );

    RootComponent = EnemyMesh;

    // Mesh por defecto
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
        ConeAsset(
            TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'")
        );

    if (ConeAsset.Succeeded())
    {
        EnemyMesh->SetStaticMesh(
            ConeAsset.Object
        );
    }

    // Valores iniciales
    MovementSpeed = 300.0f;

    AcceptanceRadius = 50.0f;

    CurrentPointIndex = 0;

    Score = 10;

    ScoreIncrement = 20;
}


// BeginPlay
void AEnemy2::BeginPlay()
{
    Super::BeginPlay();
}


// Tick
void AEnemy2::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Si hay puntos
    if (PatrolPoints.Num() > 0)
    {
        GoTo(
            PatrolPoints[CurrentPointIndex],
            DeltaTime
        );
    }
}


// Movimiento
void AEnemy2::GoTo(
    APointerActor* Target,
    float DeltaTime
)
{
    // Validar punto
    if (Target == nullptr) return;

    FVector CurrentLocation =
        GetActorLocation();

    FVector TargetLocation =
        Target->GetActorLocation();

    float DistanceToTarget =
        FVector::Dist(
            CurrentLocation,
            TargetLocation
        );

    // Llegó al punto
    if (DistanceToTarget <= AcceptanceRadius)
    {
        // =========================
        // SCORE
        // =========================

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1,
                2.0f,
                FColor::Green,
                FString::Printf(
                    TEXT("Score: %d"),
                    Score
                )
            );
        }

        // Siguiente score
        Score += ScoreIncrement;


        // =========================
        // DICTIONARY
        // =========================

        APointerActor* Point =
            PatrolPoints[CurrentPointIndex];

        AStaticMeshActor* Cube =
            Point->LinkedCube;

        if (IsValid(Cube))
        {
            UE_LOG(
                LogTemp,
                Warning,
                TEXT("Cubo encontrado")
            );

            // Obtener mesh
            UStaticMeshComponent* MeshComp =
                Cube->GetStaticMeshComponent();

            if (MeshComp)
            {
                // Obtener material
                UMaterialInterface* Material =
                    MeshComp->GetMaterial(0);

                if (Material)
                {
                    // Agregar al Dictionary
                    // Si el material ya existe:
                    // reemplaza automáticamente
                    Dictionary.Add(
                        Material,
                        Cube
                    );

                    UE_LOG(
                        LogTemp,
                        Warning,
                        TEXT("Material registrado")
                    );
                }
            }
        }
        else
        {
            UE_LOG(
                LogTemp,
                Error,
                TEXT("NO hay cubo asociado")
            );
        }


        // =========================
        // SIGUIENTE PUNTO
        // =========================

        CurrentPointIndex =
            (CurrentPointIndex + 1)
            % PatrolPoints.Num();


        // =========================
        // CICLO COMPLETADO
        // =========================

        if (CurrentPointIndex == 0)
        {
            UE_LOG(
                LogTemp,
                Warning,
                TEXT("Ciclo completado")
            );

            // Recorrer dictionary
            for (auto& Tupla : Dictionary)
            {
                if (IsValid(Tupla.Value))
                {
                    // Destruir cubo
                    Tupla.Value->Destroy();

                    Tupla.Value = nullptr;
                }
            }

            // Limpiar dictionary
            Dictionary.Empty();
        }


        // =========================
        // CAMBIO DE MESH
        // =========================

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
        // =========================
        // MOVIMIENTO
        // =========================

        FVector Direction =
            (TargetLocation - CurrentLocation)
            .GetSafeNormal();

        FVector NewLocation =
            CurrentLocation +
            (Direction *
                MovementSpeed *
                DeltaTime);

        SetActorLocation(NewLocation);
    }
}