#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy2.generated.h"

class APointerActor;

UCLASS()
class PROJECTSIS457_API AEnemy2 : public AActor
{
	GENERATED_BODY()

public:
	// Constructor
	AEnemy2();

protected:
	// Se ejecuta al iniciar el juego
	virtual void BeginPlay() override;

public:
	// Se ejecuta en cada frame
	virtual void Tick(float DeltaTime) override;

	// Malla visible del enemigo
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual")
	UStaticMeshComponent* EnemyMesh;

	// Lista de formas que puede adoptar el enemigo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	TArray<UStaticMesh*> Meshes;

	// Puntos que definen la ruta de patrulla
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Movement")
	TArray<APointerActor*> PatrolPoints;

	// Velocidad de movimiento (unidades por segundo)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementSpeed;

	// Distancia mínima para considerar que llegó al punto
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float AcceptanceRadius;

	// Puntuación actual
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int32 Score;

	// Cantidad que se suma cada vez
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int32 ScoreIncrement;

private:

	// Índice del punto actual en la patrulla
	int32 CurrentPointIndex = 0;

	// Mueve el enemigo hacia el punto objetivo
	void GoTo(APointerActor* Target, float DeltaTime);
};