#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameStateBase.h"

#include "MyGameState.generated.h"

UCLASS()
class AMyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastTest();
};
