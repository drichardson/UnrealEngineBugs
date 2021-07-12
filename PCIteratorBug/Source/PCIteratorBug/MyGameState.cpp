#include "MyGameState.h"

#include "FixedIterators.h"

#define USE_FIXED_ITERATORS

void AMyGameState::MulticastTest_Implementation()
{
	if (GetWorld()->GetNetMode() != NM_Client)
	{
		// skip server tests on client, we already did that in AMyGameMode.
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("############## AMyGameState::MulticastTest ###################"));

	UE_LOG(LogTemp, Log, TEXT("ServerAll Iteration on client. This should crash but does not."));
	for (TPlayerControllerIterator<APlayerController>::ServerAll It(GetWorld()); It; ++It)
	{
		UE_LOG(LogTemp,
			   Log,
			   TEXT("  BROKEN: Should have crashed: PlayerController=%s"),
			   *It->GetName());
	}

	// Uncomment this to test out fixed version which does crash.
#if 0
	for (TFixedPlayerControllerIterator<APlayerController>::ServerAll It(GetWorld()); It; ++It)
	{
		UE_LOG(LogTemp, Log, TEXT("  FIXED Found ServerAll Player Controller %s"), *It->GetName());
	}
#endif

	UE_LOG(LogTemp, Log, TEXT("LocalOnly Iteration from MyGameState MulticastTest"));

	for (TFixedPlayerControllerIterator<APlayerController>::LocalOnly It(GetWorld()); It; ++It)
	{
		UE_LOG(LogTemp, Log, TEXT("  FIXED Found LocalOnly Player Controller %s"), *It->GetName());
	}

#if 1
	// BROKEN: Should never crash, but does.
	for (TPlayerControllerIterator<APlayerController>::LocalOnly It(GetWorld()); It; ++It)
	{
		UE_LOG(LogTemp, Log, TEXT("  BROKEN Found LocalOnly Player Controller %s"), *It->GetName());
	}
#endif
}
