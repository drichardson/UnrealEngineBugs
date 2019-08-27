// Fill out your copyright notice in the Description page of Project Settings.


#include "NullDistributionGameModeBase.h"

#include "Distributions/DistributionFloat.h"

void ANullDistributionGameModeBase::BeginPlay()
{
	if (Distribution)
	{
		UE_LOG(LogTemp, Display, TEXT("Distribution class is %s, GetValue=%f"), *Distribution->StaticClass()->GetName(), Distribution->GetValue());
		Distribution->GetValue();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Distribution is NULL"));
	}
}