// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TopDownMover.generated.h"

// Enum que define las posibles direcciones de movimiento
// BlueprintType permite usarlo desde el Editor de Unreal
UENUM(BlueprintType)
enum class EMoveDirection : uint8
{
	Up        UMETA(DisplayName = "Arriba"),
	Down      UMETA(DisplayName = "Down"),
	Left      UMETA(DisplayName = "Left"),
	Right     UMETA(DisplayName = "Right"),
	UpRight   UMETA(DisplayName = "UpRight"),
	UpLeft    UMETA(DisplayName = "UpLeft"),
	DownLeft  UMETA(DisplayName = "DownLeft"),
	DownRight UMETA(DisplayName = "DownRight")
};

UCLASS()
class PROJECTSIS457_API ATopDownMover : public APawn
{
	GENERATED_BODY()

public:
	// Constructor: inicializa valores y componentes del Pawn
	ATopDownMover();

protected:
	// Se ejecuta cuando el juego inicia o el actor es creado
	virtual void BeginPlay() override;

	// Componente visual que representa el objeto en el mundo
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MeshComponent;

public:
	// Se ejecuta en cada frame del juego
	virtual void Tick(float DeltaTime) override;

	// Configura las entradas (input) del jugador
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Velocidad de movimiento del objeto
	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	float Velocity;

	// Dirección actual del movimiento
	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	EMoveDirection MoveDirection;

	// Indica si el objeto está en movimiento o detenido
	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	bool bIsMoving;

private:
	// Función que alterna el estado de movimiento (activar / detener)
	void ToggleMovement();
};