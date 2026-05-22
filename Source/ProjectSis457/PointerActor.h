#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointerActor.generated.h"

class UArrowComponent;
class AStaticMeshActor;

UCLASS()
class PROJECTSIS457_API APointerActor : public AActor
{
	GENERATED_BODY()

public:

	// Constructor
	APointerActor();

	// Flecha visual
	UPROPERTY(VisibleAnywhere, Category = "Reference")
	UArrowComponent* PointHandle;

	// Cubo asociado al punto
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point Logic")
	AStaticMeshActor* LinkedCube;
};