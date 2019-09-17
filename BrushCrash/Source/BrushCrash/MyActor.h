#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "SlateBrush.h"

#include "MyActor.generated.h"

struct FMyStruct
{
	FVector2D Location;
	float Angle;
	FSlateBrush Brush;
	FLinearColor Tint;

	FMyStruct(FVector2D const& Loc, float Ang, FSlateBrush const& Brush_, FLinearColor const& Tint_)
		: Location(Loc)
		, Angle(Ang)
		, Brush(Brush)
		, Tint(Tint_)
	{
	}
};

UCLASS()
class BRUSHCRASH_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	UPROPERTY(EditAnywhere)
	FSlateBrush Brush;

	UPROPERTY(EditAnywhere)
	FSlateBrush Brush2;

	UPROPERTY(EditAnywhere)
	unsigned CopyCount;

	UPROPERTY(EditAnywhere)
	bool bUseEmplace;

	UPROPERTY(EditAnywhere)
	bool bReserveSpace;

	UPROPERTY(EditAnywhere)
	bool bUseMyTint;

	UPROPERTY(EditAnywhere)
	FLinearColor MyTint;

	void BeginPlay() override;

private:
	FSlateBrush SelectBrush();
	int BrushCounter;
};
