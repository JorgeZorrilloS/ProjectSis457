#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "PointerActor.generated.h"

UCLASS()
class PROJECTSIS457_API APointerActor : public AActor
{
	GENERATED_BODY()

public:
	// Constructor
	APointerActor();

	// Componente visual que representa el punto en el editor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference")
	UArrowComponent* PointHandle;

protected:
	// Se ejecuta al iniciar el juego
	virtual void BeginPlay() override;

public:
	// No se usa normalmente, pero se mantiene por compatibilidad
	virtual void Tick(float DeltaTime) override;

	// Componente raíz opcional si deseas extender la jerarquía
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootSceneComponent;

	// Siguiente punto en la ruta de patrulla
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Movement")
	APointerActor* NextPoint = nullptr;

};