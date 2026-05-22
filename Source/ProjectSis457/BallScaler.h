#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallScaler.generated.h"

// Forward declarations
class UStaticMeshComponent;
class UPrimitiveComponent;

UCLASS()
class PROJECTSIS457_API ABallScaler : public AActor
{
    GENERATED_BODY()

public:

    // Constructor
    ABallScaler();

protected:

    // Se ejecuta al iniciar el juego
    virtual void BeginPlay() override;

    // Componente visual
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* MeshComponent;

public:

    // Se ejecuta cada frame
    virtual void Tick(float DeltaTime) override;

    // =========================
    // MOVEMENT
    // =========================

    // Velocidad de movimiento
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MovementSpeed;

    // Dirección actual
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    FVector MovementDirection;

    // Estado de movimiento
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bIsMoving;

    // =========================
    // SCALING
    // =========================

    // Velocidad de crecimiento
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scaling")
    FVector ScaleRate;

    // Estado de escalado
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scaling")
    bool bIsScaling;

private:

    // =========================
    // MOVEMENT FUNCTIONS
    // =========================

    void MoveUp();

    void MoveDown();

    void MoveLeft();

    void MoveRight();

    // Activar / detener movimiento
    void ToggleMovement();

    // =========================
    // SCALE FUNCTIONS
    // =========================

    void ToggleScaling();

    // =========================
    // MOUSE EVENT
    // =========================

    UFUNCTION()
    void OnObjectClicked(
        UPrimitiveComponent* TouchedComponent,
        FKey ButtonPressed
    );
};