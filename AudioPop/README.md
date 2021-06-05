# Update
Possible fix here:
https://github.com/EpicGames/UnrealEngine/pull/8110/files

# Audio Pop when using AudioModulation Control Bus Mixes

AudioModulation Control Bus Mix with Volume set to 0 does not effect audio
played in BeginPlay after Control Bus Mix as been activated.

See [YouTube Demonstration of problem](https://youtu.be/mvo1vnXT8ek).

## Steps to Reproduce

1. Open the Audio Modulation level
2. Run PIE

## Result

You can hear a little blip of audio, even though the Control Bus Mixes set the
audio level to -60 dB in BeginPlay in the level blueprint.
