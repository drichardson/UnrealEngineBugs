# Occlusion Problem

Demonstrates problem in UE4 where incorrect occlusion culling does not render items that should be visible.

[YouTube demo of problem](https://www.youtube.com/watch?v=qCqvRDISoW8)

The scene consists of:
- floor made up of a grid of planes
- a large plane beneath the floor that has a strongly emissive material, to make the problem more obvious
- a scaled up cube which acts as an occluding object
- a camera that interpolates between two points

When r.AllowOcclusionQueries=1, the problems occurs. When r.AllowOcclusionQueries=0, the problem does not occur.

This problem does not occur when Hierarchical Z-buffering algorithm is selected for occlusion culling by setting the following in DefaultEngine.ini:

```
[/Script/Engine.RendererSettings]
r.AllowOcclusionQueries=True
r.HZBOcclusion=1
```


See screenshot for to see what problem looks like.

![Problem Screenshot](https://github.com/drichardson/ue4bugs/blob/master/OcclusionProblem/IncorrectCulling.png)
