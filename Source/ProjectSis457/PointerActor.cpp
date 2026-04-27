#include "PointerActor.h"
#include "Components/ArrowComponent.h"
#include "Components/DecalComponent.h"

// Constructor
APointerActor::APointerActor()
{
    // Este actor solo sirve como referencia en el espacio, 
    // por lo que no necesita actualizarse cada frame
    PrimaryActorTick.bCanEverTick = false;

    // Crear el componente visual que indica la dirección del punto
    PointHandle = CreateDefaultSubobject<UArrowComponent>(TEXT("PointHandle"));

    // Definir el componente como raíz del actor
    RootComponent = PointHandle;

    // Inicialmente no hay un siguiente punto
    NextPoint = nullptr;
}

// Se ejecuta al iniciar el juego
void APointerActor::BeginPlay()
{
    Super::BeginPlay();
}

// No se usa Tick, pero se mantiene por compatibilidad
void APointerActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}