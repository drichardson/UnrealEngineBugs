#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"

#include "MyGameMode.generated.h"

UCLASS()
class PCITERATORBUG_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameMode();
	void BeginPlay() override;

private:
	FTimerHandle TestTimerHandle;
	void TestTimer();
};
