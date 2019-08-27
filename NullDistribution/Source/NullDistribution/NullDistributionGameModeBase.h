// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NullDistributionGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class NULLDISTRIBUTION_API ANullDistributionGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	class UDistributionFloat* Distribution;

	void BeginPlay() override;
};
