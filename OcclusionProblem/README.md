# Occlusion Problem

Demonstrates problem in UE4 where incorrect occlusion culling does not render items that should be visible.

The scene consists of:
- floor made up of a grid of planes
- a large plane beneath the floor that has a strongly emissive material, to make the problem more obvious
- a scaled up cube which acts as an occluding object
- a camera that interpolates between two points

When r.AllowOcclusionQueries=1, the problems occurs. When r.AllowOcclusionQueries=0, the problem does not occur.

See screenshot for to see what problem looks like.
