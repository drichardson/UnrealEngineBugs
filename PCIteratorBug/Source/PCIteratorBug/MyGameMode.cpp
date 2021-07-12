#include "MyGameMode.h"

#include "MyGameState.h"

AMyGameMode::AMyGameMode()
{
	GameStateClass = AMyGameState::StaticClass();
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TestTimerHandle, this, &AMyGameMode::TestTimer, 2.0f, true);
}

void AMyGameMode::TestTimer()
{
	UE_LOG(LogTemp, Log, TEXT("##################################################"));
	UE_LOG(LogTemp, Log, TEXT("LocalOnly Iteration from GameMode BeginPlay"));

	for (TPlayerControllerIterator<APlayerController>::LocalOnly It(GetWorld()); It; ++It)
	{
		UE_LOG(LogTemp, Log, TEXT("  Found LocalOnly Player Controller %s"), *It->GetName());
	}

	UE_LOG(LogTemp, Log, TEXT("ServerAll Iteration from AGameMode::TestTimer"));

	for (TPlayerControllerIterator<APlayerController>::ServerAll It(GetWorld()); It; ++It)
	{
		UE_LOG(LogTemp, Log, TEXT("  Found ServerAll Player Controller %s"), *It->GetName());
	}

	GetGameState<AMyGameState>()->MulticastTest();
}
