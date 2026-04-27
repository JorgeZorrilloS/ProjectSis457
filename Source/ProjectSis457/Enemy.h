#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

class APointerActor;

UCLASS()
class PROJECTSIS457_API AEnemy : public AActor
{
    GENERATED_BODY()

public:
    // Constructor
    AEnemy();

protected:
    // Se ejecuta al iniciar el juego
    virtual void BeginPlay() override;

public:
    // Se ejecuta en cada frame
    virtual void Tick(float DeltaTime) override;

    // Malla visible del enemigo
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual")
    UStaticMeshComponent* EnemyMesh;

    // Lista de formas que el enemigo puede usar
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    TArray<UStaticMesh*> Meshes;

    // Punto actual hacia donde se mueve el enemigo
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Movement")
    APointerActor* TargetPoint;

    // Velocidad de movimiento (unidades por segundo)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MovementSpeed = 300.0f;

    // Distancia mínima para considerar que llegó al objetivo
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float AcceptanceRadius = 50.0f;

private:

    // Índice interno de la malla actual
    int32 CurrentMeshIndex = 0;

};