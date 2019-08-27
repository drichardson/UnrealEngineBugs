# CompileAllBlueprints Commandlet Crashes on 4.22

## Steps to Repro
1. Create a new empty blueprint only project in 4.22.1.
2. Run the following commandlet (replacing the path to UE4 and to the new project for your system):

```
C:\UnrealEngine\UE_4.22\Engine\Binaries\Win64\UE4Editor-Cmd.exe E:\code\ue4bugs\CompileBPCommandlet\CompileBPCommandlet.uproject -run=CompileAllBlueprints
```


## Result
The following crash occurs. See CompileBPCommandlet.log for the entire log.

```
[2019.05.03-19.02.30:270][  0]LogCompileAllBlueprintsCommandlet: Display: Loading Kismit Blueprint Compiler...
[2019.05.03-19.02.30:271][  0]LogCompileAllBlueprintsCommandlet: Display: Finished Loading Kismit Blueprint Compiler...
[2019.05.03-19.02.30:272][  0]LogCompileAllBlueprintsCommandlet: Display: Loading Asset Registry...
[2019.05.03-19.02.30:365][  0]LogCompileAllBlueprintsCommandlet: Display: Finished Loading Asset Registry.
[2019.05.03-19.02.30:365][  0]LogCompileAllBlueprintsCommandlet: Display: Gathering All Blueprints From Asset Registry...
[2019.05.03-19.02.30:368][  0]LogCompileAllBlueprintsCommandlet: Display: Loading and Compiling: '/Engine/EngineDamageTypes/DmgTypeBP_Environmental.DmgTypeBP_Environmental'...
[2019.05.03-19.02.30:368][  0]LogOutputDevice: Warning: 

Script Stack (0 frames):

[2019.05.03-19.02.30:369][  0]LogWindows: Windows GetLastError: The operation completed successfully. (0)
[2019.05.03-19.02.32:939][  0]LogWindows: Error: === Critical error: ===
[2019.05.03-19.02.32:939][  0]LogWindows: Error: 
[2019.05.03-19.02.32:940][  0]LogWindows: Error: Assertion failed: (Index >= 0) & (Index < ArrayNum) [File:D:\Build\++UE4\Sync\Engine\Source\Runtime\Core\Public\Containers/Array.h] [Line: 611] 
[2019.05.03-19.02.32:941][  0]LogWindows: Error: Array index out of bounds: 3 from an array of size 0
[2019.05.03-19.02.32:942][  0]LogWindows: Error: 
[2019.05.03-19.02.32:943][  0]LogWindows: Error: 
[2019.05.03-19.02.32:943][  0]LogWindows: Error: [Callstack] 0x00007ffa1b0a9129 KERNELBASE.dll!UnknownFunction []
[2019.05.03-19.02.32:944][  0]LogWindows: Error: [Callstack] 0x00007ff9e2db1f07 UE4Editor-Core.dll!ReportAssert() [d:\build\++ue4\sync\engine\source\runtime\core\private\windows\windowsplatformcrashcontext.cpp:553]
[2019.05.03-19.02.32:945][  0]LogWindows: Error: [Callstack] 0x00007ff9e2db46b7 UE4Editor-Core.dll!FWindowsErrorOutputDevice::Serialize() [d:\build\++ue4\sync\engine\source\runtime\core\private\windows\windowserroroutputdevice.cpp:79]
[2019.05.03-19.02.32:947][  0]LogWindows: Error: [Callstack] 0x00007ff9e2bc7cea UE4Editor-Core.dll!FOutputDevice::LogfImpl() [d:\build\++ue4\sync\engine\source\runtime\core\private\misc\outputdevice.cpp:71]
[2019.05.03-19.02.32:947][  0]LogWindows: Error: [Callstack] 0x00007ff9e2b4fe07 UE4Editor-Core.dll!FDebug::AssertFailed() [d:\build\++ue4\sync\engine\source\runtime\core\private\misc\assertionmacros.cpp:440]
[2019.05.03-19.02.32:948][  0]LogWindows: Error: [Callstack] 0x00007ff9e2b50499 UE4Editor-Core.dll!FDebug::CheckVerifyFailedImpl() [d:\build\++ue4\sync\engine\source\runtime\core\private\misc\assertionmacros.cpp:418]
[2019.05.03-19.02.32:949][  0]LogWindows: Error: [Callstack] 0x00007ff9c2142778 UE4Editor-UnrealEd.dll!DispatchCheckVerify<void,<lambda_023adc04eb97b0d12b89425341d4205f> >() [d:\build\++ue4\sync\engine\source\runtime\core\public\misc\assertionmacros.h:162]
[2019.05.03-19.02.32:952][  0]LogWindows: Error: [Callstack] 0x00007ff9c199a80e UE4Editor-UnrealEd.dll!FBlueprintEditorUtils::PatchNewCDOIntoLinker() [d:\build\++ue4\sync\engine\source\editor\unrealed\private\kismet2\blueprinteditorutils.cpp:724]
[2019.05.03-19.02.32:953][  0]LogWindows: Error: [Callstack] 0x00007ff9df888f4d UE4Editor-KismetCompiler.dll!FKismetCompilerContext::CompileFunctions() [d:\build\++ue4\sync\engine\source\editor\kismetcompiler\private\kismetcompiler.cpp:4195]
[2019.05.03-19.02.32:955][  0]LogWindows: Error: [Callstack] 0x00007ff9df8849c9 UE4Editor-KismetCompiler.dll!FKismet2CompilerModule::CompileBlueprintInner() [d:\build\++ue4\sync\engine\source\editor\kismetcompiler\private\kismetcompilermodule.cpp:133]
[2019.05.03-19.02.32:955][  0]LogWindows: Error: [Callstack] 0x00007ff9df884212 UE4Editor-KismetCompiler.dll!FKismet2CompilerModule::CompileBlueprint() [d:\build\++ue4\sync\engine\source\editor\kismetcompiler\private\kismetcompilermodule.cpp:235]
[2019.05.03-19.02.32:956][  0]LogWindows: Error: [Callstack] 0x00007ff9c138ed10 UE4Editor-UnrealEd.dll!UCompileAllBlueprintsCommandlet::CompileBlueprint() [d:\build\++ue4\sync\engine\source\editor\unrealed\private\commandlets\compileallblueprintscommandlet.cpp:321]
[2019.05.03-19.02.32:956][  0]LogWindows: Error: [Callstack] 0x00007ff9c138ae7e UE4Editor-UnrealEd.dll!UCompileAllBlueprintsCommandlet::BuildBlueprints() [d:\build\++ue4\sync\engine\source\editor\unrealed\private\commandlets\compileallblueprintscommandlet.cpp:157]
[2019.05.03-19.02.32:957][  0]LogWindows: Error: [Callstack] 0x00007ff9c13be1b6 UE4Editor-UnrealEd.dll!UCompileAllBlueprintsCommandlet::Main() [d:\build\++ue4\sync\engine\source\editor\unrealed\private\commandlets\compileallblueprintscommandlet.cpp:39]
[2019.05.03-19.02.32:958][  0]LogWindows: Error: [Callstack] 0x00007ff605ede402 UE4Editor-Cmd.exe!FEngineLoop::PreInit() [d:\build\++ue4\sync\engine\source\runtime\launch\private\launchengineloop.cpp:2706]
[2019.05.03-19.02.32:958][  0]LogWindows: Error: [Callstack] 0x00007ff605ed5377 UE4Editor-Cmd.exe!GuardedMain() [d:\build\++ue4\sync\engine\source\runtime\launch\private\launch.cpp:129]
[2019.05.03-19.02.32:959][  0]LogWindows: Error: [Callstack] 0x00007ff605ed55ca UE4Editor-Cmd.exe!GuardedMainWrapper() [d:\build\++ue4\sync\engine\source\runtime\launch\private\windows\launchwindows.cpp:145]
[2019.05.03-19.02.32:959][  0]LogWindows: Error: [Callstack] 0x00007ff605ee316c UE4Editor-Cmd.exe!WinMain() [d:\build\++ue4\sync\engine\source\runtime\launch\private\windows\launchwindows.cpp:275]
[2019.05.03-19.02.32:959][  0]LogWindows: Error: [Callstack] 0x00007ff605ee4cb6 UE4Editor-Cmd.exe!__scrt_common_main_seh() [d:\agent\_work\3\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl:288]
[2019.05.03-19.02.32:960][  0]LogWindows: Error: [Callstack] 0x00007ffa1dc47974 KERNEL32.DLL!UnknownFunction []
[2019.05.03-19.02.32:964][  0]LogWindows: Error: [Callstack] 0x00007ffa1e44a271 ntdll.dll!UnknownFunction []
[2019.05.03-19.02.32:965][  0]LogWindows: Error: 
[2019.05.03-19.02.32:977][  0]LogExit: Executing StaticShutdownAfterError
[2019.05.03-19.02.32:979][  0]LogWindows: FPlatformMisc::RequestExit(1)
[2019.05.03-19.02.32:988][  0]Log file closed, 05/03/19 12:02:32
```



