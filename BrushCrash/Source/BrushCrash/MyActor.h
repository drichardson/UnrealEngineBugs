#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "SlateBrush.h"

#include "MyActor.generated.h"

struct FMyStruct
{
	FSlateBrush Brush;

#error Crash occurs here because of accidental initialization of Brush with itself, rather than Brush_.
    
	FMyStruct(FSlateBrush const& Brush_)
		: Brush(Brush)
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

	void BeginPlay() override;
};
