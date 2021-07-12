#include "MyGameMode.h"

#include "FixedIterators.h"
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
	UE_LOG(LogTemp, Log, TEXT("############## AMyGameMode::TestTimer ###################"));

	UE_LOG(LogTemp, Log, TEXT("LocalOnly Iteration from GameMode"));
	for (TPlayerControllerIterator<APlayerController>::LocalOnly It(GetWorld()); It; ++It)
	{
		UE_LOG(LogTemp, Log, TEXT("  Found LocalOnly Player Controller %s"), *It->GetName());
	}

	UE_LOG(LogTemp, Log, TEXT("ServerAll Iteration from AGameMode::TestTimer"));
	for (TPlayerControllerIterator<APlayerController>::ServerAll It(GetWorld()); It; ++It)
	{
		UE_LOG(LogTemp, Log, TEXT("  Found ServerAll Player Controller %s"), *It->GetName());
	}

	// ***************************************************
	// Make sure fixed iterators do not crash on server.
	// ***************************************************
	UE_LOG(LogTemp, Log, TEXT("FIXED LocalOnly Iteration from GameMode"));
	for (TFixedPlayerControllerIterator<APlayerController>::LocalOnly It(GetWorld()); It; ++It)
	{
		UE_LOG(LogTemp, Log, TEXT("  FIXED Found LocalOnly Player Controller %s"), *It->GetName());
	}

	UE_LOG(LogTemp, Log, TEXT("FIXED ServerAll Iteration from AGameMode::TestTimer"));
	for (TFixedPlayerControllerIterator<APlayerController>::ServerAll It(GetWorld()); It; ++It)
	{
		UE_LOG(LogTemp, Log, TEXT("  FIXED Found ServerAll Player Controller %s"), *It->GetName());
	}

	//
	// Run tests on client.
	//
	GetGameState<AMyGameState>()->MulticastTest();
}
