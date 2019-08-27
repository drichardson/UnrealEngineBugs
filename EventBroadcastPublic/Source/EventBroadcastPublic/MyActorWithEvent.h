// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActorWithEvent.generated.h"

UCLASS()
class EVENTBROADCASTPUBLIC_API AMyActorWithEvent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActorWithEvent();

	DECLARE_EVENT(AMyActorWithEvent, FMyTestEvent)
	FMyTestEvent& OnMyTestEventOccurred() { return MyTestEvent; }

	void CallBroadcast()
	{
		// This should compile since AMyActorWithEvent is the owner specified in DECLARE_EVENT.
		MyTestEvent.Broadcast();
	}

private:
	FMyTestEvent MyTestEvent;
};
