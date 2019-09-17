#include "MyActor.h"

#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMyActor, Log, All);
DEFINE_LOG_CATEGORY(LogMyActor);

static FMyStruct SetupMyStruct(AMyActor const* Actor, FSlateBrush const& Brush)
{
	return FMyStruct(Brush);
}

AMyActor::AMyActor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshOb(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	MeshComponent->SetStaticMesh(StaticMeshOb.Object);

	RootComponent = MeshComponent;
}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	// Run tests in begin play so this doesn't crash in editor before play.

	// crashes
	FMyStruct F = SetupMyStruct(this, Brush);
}



