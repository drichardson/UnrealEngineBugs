# Update
Possible fix here:
https://github.com/EpicGames/UnrealEngine/pull/8110/files

# Summary
Demonstrates same propblem as AudioPop, execpt in UE 4 master (tested with
github commit b27b32b366936d24000fe0b31288420b3a55d3b2).

Audio Modulation plugin is enabled.

A single sound is added to the Audio Modulation level that has an Override volume modulation set to -60.

No ConrolBus or ControlBusMix is used.
