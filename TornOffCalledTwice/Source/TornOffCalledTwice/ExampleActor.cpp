#include "ExampleActor.h"

#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY_STATIC(LogExampleActor, Log, All);

AExampleActor::AExampleActor()
{
	UE_LOG(LogExampleActor, Log, TEXT("AExampleActor::AExampleActor"));
	bReplicates = true;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void AExampleActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AExampleActor, Counter);
}

void AExampleActor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		UE_LOG(LogExampleActor, Log, TEXT("Setting timer to tear off actor"));
		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, this, &AExampleActor::OnTimerFired, 5.0f, false);

		SetActorTickEnabled(true);
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

#if 0
	Destroy();
#else
	// TornOff will be called when lifespan expired.
	SetLifeSpan(1.0f);
#endif
}

void AExampleActor::TornOff()
{
	Super::TornOff();
	UE_LOG(LogExampleActor, Log, TEXT("AExampleActor::TornOff"));
}

void AExampleActor::Tick(float DeltaSeconds)
{
	check(HasAuthority());
	Super::Tick(DeltaSeconds);
	Counter++;
}

void AExampleActor::OnRep_Counter()
{
	check(!HasAuthority());
	UE_LOG(LogExampleActor, Log, TEXT("Counter=%d TearOff=%d"), Counter, GetTearOff());
}

void AExampleActor::LifeSpanExpired()
{
	UE_LOG(LogExampleActor,
		   Log,
		   TEXT("LifeSpanExpired: Counter=%d TearOff=%d Authority=%d"),
		   Counter,
		   GetTearOff(),
		   HasAuthority());

	Super::LifeSpanExpired();
}
