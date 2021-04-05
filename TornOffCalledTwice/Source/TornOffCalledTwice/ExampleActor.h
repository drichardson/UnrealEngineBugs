#pragma once

#include "CoreMinimal.h"

#include "ExampleActor.generated.h"

UCLASS()
class AExampleActor : public AActor
{
	GENERATED_BODY()

public:
	AExampleActor();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	void BeginPlay() override;
	void TornOff() override;
	void Tick(float DeltaSeconds) override;
	void LifeSpanExpired() override;

	UPROPERTY(ReplicatedUsing = OnRep_Counter, Transient)
	int Counter;

	UFUNCTION()
	void OnRep_Counter();

private:
	void OnTimerFired();
};
