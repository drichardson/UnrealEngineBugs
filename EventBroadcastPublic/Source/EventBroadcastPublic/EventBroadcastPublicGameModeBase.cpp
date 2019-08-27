// Fill out your copyright notice in the Description page of Project Settings.

#include "EventBroadcastPublicGameModeBase.h"
#include "MyActorWithEvent.h"
#include "EngineUtils.h"
#include "MyActorWithEvent.h"

void AEventBroadcastPublicGameModeBase::Foo()
{
	AMyActorWithEvent* myActor = nullptr;

	// THIS SHOULD NOT COMPILE.
	myActor->OnMyTestEventOccurred().Broadcast();
}
