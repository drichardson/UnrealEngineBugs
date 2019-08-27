#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCppActor.generated.h"

// My C++ Actor Class
UCLASS(BlueprintType, Blueprintable)
class AMyCppActor : public AActor
{
	GENERATED_BODY()

public:

	AMyCppActor();

	UPROPERTY(EditAnywhere)
	class USphereComponent* Sphere;
};
