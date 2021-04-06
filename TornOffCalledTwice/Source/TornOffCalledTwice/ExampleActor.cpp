#include "ExampleActor.h"

#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY_STATIC(LogExampleActor, Log, All);

static TAutoConsoleVariable<float> CVarExampleActorLifeSpan(
	TEXT("ExampleActorLifeSpan"), 2.0f, TEXT("LifeSpan of example actor after TearOff called."));

AExampleActor::AExampleActor()
{
	UE_LOG(LogExampleActor, Log, TEXT("AExampleActor::AExampleActor"));
	bReplicates = true;

	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void AExampleActor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		UE_LOG(LogExampleActor, Log, TEXT("Setting timer to tear off actor in 2 seconds..."));
		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, this, &AExampleActor::OnTimerFired, 2.0f, false);
	}
	else
	{
		UE_LOG(LogExampleActor, Log, TEXT("Does not have authority, will wait for TornOff"));
	}
}

void AExampleActor::OnTimerFired()
{
	check(HasAuthority());
	UE_LOG(LogExampleActor, Log, TEXT("OnTimerFired. Calling TearOff"));
	TearOff();

	//
	// BUG HERE: If SetLifeSpan is called, TornOff will be called twice.
	//
	// TornOff will be called when lifespan expired.
	float const LifeSpan = CVarExampleActorLifeSpan.GetValueOnGameThread();
	UE_LOG(LogExampleActor, Log, TEXT("Calling SetLifeSpan(%f)"), LifeSpan);
	SetLifeSpan(LifeSpan);
}

void AExampleActor::TornOff()
{
	Super::TornOff();
	TornOffCounter++;
	UE_LOG(LogExampleActor, Log, TEXT("AExampleActor::TornOff called %d times"), TornOffCounter);
}

void AExampleActor::LifeSpanExpired()
{
	UE_LOG(LogExampleActor,
		   Log,
		   TEXT("LifeSpanExpired: TearOff=%d Authority=%d"),
		   GetTearOff(),
		   HasAuthority());

	Super::LifeSpanExpired();
}
