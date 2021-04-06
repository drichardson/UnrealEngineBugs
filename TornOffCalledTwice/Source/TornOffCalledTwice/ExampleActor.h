#pragma once

#include "CoreMinimal.h"

#include "ExampleActor.generated.h"

UCLASS()
class AExampleActor : public AActor
{
	GENERATED_BODY()

public:
	AExampleActor();

	void BeginPlay() override;
	void TornOff() override;
	void LifeSpanExpired() override;

private:
	void OnTimerFired();

	int TornOffCounter = 0;
};
