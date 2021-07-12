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
[2021.07.12-20.42.48:930][452]LogTemp: ############## AMyGameMode::TestTimer ###################
[2021.07.12-20.42.48:931][452]LogTemp: LocalOnly Iteration from GameMode
[2021.07.12-20.42.48:931][452]LogTemp: ServerAll Iteration from AGameMode::TestTimer
[2021.07.12-20.42.48:932][452]LogTemp:   Found ServerAll Player Controller PlayerController_0
[2021.07.12-20.42.48:932][452]LogTemp: FIXED LocalOnly Iteration from GameMode
[2021.07.12-20.42.48:933][452]LogTemp: FIXED ServerAll Iteration from AGameMode::TestTimer
[2021.07.12-20.42.48:934][452]LogTemp:   FIXED Found ServerAll Player Controller PlayerController_0
[2021.07.12-20.42.48:999][460]LogTemp: ############## AMyGameState::MulticastTest ###################
[2021.07.12-20.42.49:000][460]LogTemp: ServerAll Iteration on client. This should crash but does not.
[2021.07.12-20.42.49:001][460]LogTemp:   BROKEN: Should have crashed: PlayerController=PlayerController_1
[2021.07.12-20.42.49:001][460]LogTemp: LocalOnly Iteration from MyGameState MulticastTest
[2021.07.12-20.42.49:002][460]LogTemp:   FIXED Found LocalOnly Player Controller PlayerController_1
[2021.07.12-20.42.49:002][460]LogOutputDevice: Warning: 

Script Stack (1 frames):
MyGameState.MulticastTest

[2021.07.12-20.42.49:003][460]LogWindows: Windows GetLastError: The operation completed successfully. (0)
[2021.07.12-20.43.03:387][460]LogWindows: Error: === Critical error: ===
[2021.07.12-20.43.03:388][460]LogWindows: Error: 
[2021.07.12-20.43.03:389][460]LogWindows: Error: Assertion failed: !LocalOnly || InWorld->GetNetMode() != NM_Client [File:C:\UnrealEngine\UE_4.26\Engine\Source\Runtime\Engine\Public\UnrealEngine.h] [Line: 107] 
[2021.07.12-20.43.03:389][460]LogWindows: Error: 
[2021.07.12-20.43.03:390][460]LogWindows: Error: 
[2021.07.12-20.43.03:391][460]LogWindows: Error: 
[2021.07.12-20.43.03:391][460]LogWindows: Error: [Callstack] 0x00007ff8f19f4ed9 KERNELBASE.dll!UnknownFunction []
[2021.07.12-20.43.03:392][460]LogWindows: Error: [Callstack] 0x00007ff8b7c8d066 UE4Editor-Core.dll!ReportAssert() [D:\Build\++UE4\Sync\Engine\Source\Runtime\Core\Private\Windows\WindowsPlatformCrashContext.cpp:1616]
[2021.07.12-20.43.03:392][460]LogWindows: Error: [Callstack] 0x00007ff8b7c907a8 UE4Editor-Core.dll!FWindowsErrorOutputDevice::Serialize() [D:\Build\++UE4\Sync\Engine\Source\Runtime\Core\Private\Windows\WindowsErrorOutputDevice.cpp:78]
[2021.07.12-20.43.03:393][460]LogWindows: Error: [Callstack] 0x00007ff8b799e8cd UE4Editor-Core.dll!FOutputDevice::LogfImpl() [D:\Build\++UE4\Sync\Engine\Source\Runtime\Core\Private\Misc\OutputDevice.cpp:61]
[2021.07.12-20.43.03:393][460]LogWindows: Error: [Callstack] 0x00007ff8b7935575 UE4Editor-Core.dll!AssertFailedImplV() [D:\Build\++UE4\Sync\Engine\Source\Runtime\Core\Private\Misc\AssertionMacros.cpp:104]
[2021.07.12-20.43.03:394][460]LogWindows: Error: [Callstack] 0x00007ff8b7937620 UE4Editor-Core.dll!FDebug::CheckVerifyFailedImpl() [D:\Build\++UE4\Sync\Engine\Source\Runtime\Core\Private\Misc\AssertionMacros.cpp:461]
[2021.07.12-20.43.03:394][460]LogWindows: Error: [Callstack] 0x00007ff86de83526 UE4Editor-PCIteratorBug.dll!AMyGameState::MulticastTest_Implementation() [F:\UnrealEngineBugs\PCIteratorBug\Source\PCIteratorBug\MyGameState.cpp:43]
[2021.07.12-20.43.03:394][460]LogWindows: Error: [Callstack] 0x00007ff8b70c2604 UE4Editor-CoreUObject.dll!UFunction::Invoke() [D:\Build\++UE4\Sync\Engine\Source\Runtime\CoreUObject\Private\UObject\Class.cpp:5588]
```
