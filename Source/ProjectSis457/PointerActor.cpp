#include "PointerActor.h"

#include "Components/ArrowComponent.h"
#include "Engine/StaticMeshActor.h"


// Constructor
APointerActor::APointerActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // Crear flecha
    PointHandle =
        CreateDefaultSubobject<UArrowComponent>(
            TEXT("PointHandle")
        );

    // Root
    RootComponent = PointHandle;
}