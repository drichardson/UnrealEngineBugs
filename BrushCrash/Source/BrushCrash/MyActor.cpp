#include "MyActor.h"

#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

DECLARE_LOG_CATEGORY_EXTERN(MyActor, Log, All);
DEFINE_LOG_CATEGORY(MyActor);

static FMyStruct SetupMyStruct(AMyActor const* Actor, FSlateBrush const& Brush)
{
	FVector Location3D = Actor->GetActorLocation();
	FVector2D Location = FVector2D(Location3D.X, Location3D.Y);
	float Angle = FMath::DegreesToRadians(Actor->GetActorRotation().Yaw);

	FLinearColor Tint;
	if (Actor->bUseMyTint)
	{
		Tint = Actor->MyTint;
	}
	else
	{
		Tint = FLinearColor::Red;
	}

	return FMyStruct(Location, Angle, Brush, Tint);
}

AMyActor::AMyActor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshOb(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	MeshComponent->SetStaticMesh(StaticMeshOb.Object);

	RootComponent = MeshComponent;

	CopyCount = 10;
	bUseEmplace = false;
	bReserveSpace = false;
	BrushCounter = 0;
	bUseMyTint = false;
	MyTint = FLinearColor::Yellow;
}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	// Run tests in begin play so this doesn't crash in editor before play.

	UE_LOG(MyActor, Log, TEXT("AMyActor::BeginPlay: Running Tests: %s"), *GetNameSafe(this));

	{
		UE_LOG(MyActor, Log, TEXT("BEGIN Brush Array Test: reserve=%d, items=%d, emplace=%d"), bReserveSpace, CopyCount, bUseEmplace);
		TArray<FSlateBrush> A;

		if (bReserveSpace)
		{
			A.Reserve(CopyCount);
		}

		if (bUseEmplace)
		{
			for (unsigned i = 0; i < CopyCount; i++)
			{
				A.Emplace(SelectBrush());
			}
		}
		else
		{
			for (unsigned i = 0; i < CopyCount; i++)
			{
				A.Add(SelectBrush());
			}
		}

		UE_LOG(MyActor, Log, TEXT("END Brush Array Test"));
	}

	{
		UE_LOG(MyActor, Log, TEXT("BEGIN FMyStruct Test: reserve=%d, items=%d, emplace=%d"), bReserveSpace, CopyCount, bUseEmplace);

		TArray<FMyStruct> A;

		if (bReserveSpace)
		{
			A.Reserve(CopyCount);
		}

		if (bUseEmplace)
		{
			for (unsigned i = 0; i < CopyCount; i++)
			{
				A.Emplace(SetupMyStruct(this, SelectBrush()));
			}
		}
		else
		{
			for (unsigned i = 0; i < CopyCount; i++)
			{
				A.Add(SetupMyStruct(this, SelectBrush()));
			}
		}

		UE_LOG(MyActor, Log, TEXT("END FMyStruct Test"));
	}
}

FSlateBrush AMyActor::SelectBrush()
{
	BrushCounter++;

	if (BrushCounter % 3 == 0)
	{
		return Brush;
	}

	return Brush2;
}
