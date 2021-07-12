# TPlayerControllerIterator bug

1. Open project.
2. Run as client.

Crash. The problem is an incorrect `check` in this template constructor:

```c++
TBasePlayerControllerIterator(class UWorld* InWorld)
        : Iter(InWorld->GetPlayerControllerIterator())
{
        check(!LocalOnly || InWorld->GetNetMode() != NM_Client);	// You should only iterate on non local player controllers if you are the server
        AdvanceCurrent();
}
```

The check line should be:

```c++
check(LocalOnly || InWorld->GetNetMode() != NM_Client);	// You should only iterate on non local player controllers if you are the server
```

A corrected version of this is in FixedIterators.h.


```
[2021.07.12-20.22.18:495][823]LogTemp: ##################################################
[2021.07.12-20.22.18:496][823]LogTemp: LocalOnly Iteration from GameMode BeginPlay
[2021.07.12-20.22.18:496][823]LogTemp: ServerAll Iteration from AGameMode::TestTimer
[2021.07.12-20.22.18:497][823]LogTemp:   Found ServerAll Player Controller PlayerController_0
[2021.07.12-20.22.18:497][823]LogTemp: MulticastTest: WorldNetMode=1
[2021.07.12-20.22.18:497][823]LogTemp: LocalOnly Iteration from MyGameState MulticastTest
[2021.07.12-20.22.18:498][823]LogTemp:   FIXED Found LocalOnly Player Controller PlayerController_0
[2021.07.12-20.22.18:547][829]LogTemp: MulticastTest: WorldNetMode=3
[2021.07.12-20.22.18:548][829]LogTemp: ServerAll Iteration on client. This should crash but does not.
[2021.07.12-20.22.18:548][829]LogTemp:   BROKEN: Should have crashed: PlayerController=PlayerController_1
[2021.07.12-20.22.18:549][829]LogTemp: LocalOnly Iteration from MyGameState MulticastTest
[2021.07.12-20.22.18:549][829]LogOutputDevice: Warning: 

Script Stack (1 frames):
MyGameState.MulticastTest

[2021.07.12-20.22.18:550][829]LogWindows: Windows GetLastError: The operation completed successfully. (0)
[2021.07.12-20.22.32:544][829]LogWindows: Error: === Critical error: ===
[2021.07.12-20.22.32:546][829]LogWindows: Error: 
[2021.07.12-20.22.32:546][829]LogWindows: Error: Assertion failed: LocalOnly || InWorld->GetNetMode() != NM_Client [File:F:\UnrealEngineBugs\PCIteratorBug\Source\PCIteratorBug\FixedIterators.h] [Line: 13] 
[2021.07.12-20.22.32:547][829]LogWindows: Error: 
[2021.07.12-20.22.32:547][829]LogWindows: Error: 
[2021.07.12-20.22.32:548][829]LogWindows: Error: 
[2021.07.12-20.22.32:549][829]LogWindows: Error: [Callstack] 0x00007ff8f19f4ed9 KERNELBASE.dll!UnknownFunction []
[2021.07.12-20.22.32:549][829]LogWindows: Error: [Callstack] 0x00007ff8c210d066 UE4Editor-Core.dll!ReportAssert() [D:\Build\++UE4\Sync\Engine\Source\Runtime\Core\Private\Windows\WindowsPlatformCrashContext.cpp:1616]
[2021.07.12-20.22.32:550][829]LogWindows: Error: [Callstack] 0x00007ff8c21107a8 UE4Editor-Core.dll!FWindowsErrorOutputDevice::Serialize() [D:\Build\++UE4\Sync\Engine\Source\Runtime\Core\Private\Windows\WindowsErrorOutputDevice.cpp:78]
[2021.07.12-20.22.32:550][829]LogWindows: Error: [Callstack] 0x00007ff8c1e1e8cd UE4Editor-Core.dll!FOutputDevice::LogfImpl() [D:\Build\++UE4\Sync\Engine\Source\Runtime\Core\Private\Misc\OutputDevice.cpp:61]
[2021.07.12-20.22.32:551][829]LogWindows: Error: [Callstack] 0x00007ff8c1db5575 UE4Editor-Core.dll!AssertFailedImplV() [D:\Build\++UE4\Sync\Engine\Source\Runtime\Core\Private\Misc\AssertionMacros.cpp:104]
[2021.07.12-20.22.32:552][829]LogWindows: Error: [Callstack] 0x00007ff8c1db7620 UE4Editor-Core.dll!FDebug::CheckVerifyFailedImpl() [D:\Build\++UE4\Sync\Engine\Source\Runtime\Core\Private\Misc\AssertionMacros.cpp:461]
[2021.07.12-20.22.32:552][829]LogWindows: Error: [Callstack] 0x00007ff8734e30b3 UE4Editor-PCIteratorBug.dll!AMyGameState::MulticastTest_Implementation() [F:\UnrealEngineBugs\PCIteratorBug\Source\PCIteratorBug\MyGameState.cpp:36]
```
