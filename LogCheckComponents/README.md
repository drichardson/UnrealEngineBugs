# LogCheckCompnents warngs when component added to blueprint sub-class

## Steps to Repro

1. Open MyLevel map.
2. View the logs. You will see:

```
LogCheckComponents: Error: SerializedComponent archetype is not the CDO nor a default subobject of my class. Me = OneComponentAdded_C /Game/MyLevel.MyLevel:PersistentLevel.OneComponentAdded_2, Component = StaticMeshComponent /Game/MyLevel.MyLevel:PersistentLevel.OneComponentAdded_2.Cube, Archetype = StaticMeshComponent /Game/OneComponentAdded.OneComponentAdd
ed_C:Cube_GEN_VARIABLE
LogCheckComponents: Error: SerializedComponent archetype is not the CDO nor a default subobject of my class. Me = OneComponentAdded_C /Game/MyLevel.MyLevel:PersistentLevel.OneComponentAdded_2, Component = StaticMeshComponent /Game/MyLevel.MyLevel:PersistentLevel.OneComponentAdded_2.Cube, Archetype = StaticMeshComponent /Game/OneComponentAdded.OneComponentAdd
ed_C:Cube_GEN_VARIABLE
LogCheckComponents: Error: SerializedComponent archetype is not the CDO nor a default subobject of my class. Me = OneComponentAdded_C /Game/MyLevel.MyLevel:PersistentLevel.OneComponentAdded_2, Component = StaticMeshComponent /Game/MyLevel.MyLevel:PersistentLevel.OneComponentAdded_2.Cube, Archetype = StaticMeshComponent /Game/OneComponentAdded.OneComponentAdd
ed_C:Cube_GEN_VARIABLE
```

## Details

This error occurs because:

1. The *OneComponentAdded* blueprint was added to MyLevel. This blueprint actor
   has a *SerializedComponent*, that is, a component that was added in the
   blueprint editor that does not exist in the native StaticMeshActor base
   class.
2. The LogCheckSubobjects log category level is set to warning. This has the side effect of enabling the CheckDefaultSubobject check. See the following line of UObject::CanCheckDefaultSubObjects for details:
    ```C++
    bCanCheck = bCanCheck && (bForceCheck || UE_LOG_ACTIVE(LogCheckSubobjects, Error));
    ```


## Core.Log

Although this bug report uses the following log to demonstrate what leads to the issue...

```
[Core.Log]
LogCheckSubobjects=warning
```

...it is more common to run into this problem by changing the global log setting like so:

```
[Core.Log]
global=warning
```

## Analysis

It isn't clear if the warning is a problem or not. It appears to be that
blueprint generated archetypes that exists in the level aren't handled by
AActor::CheckActorComponents().

Regardless, I think user's should be able to set the global log level to
warning or error, without being flooded with a bunch of errors they didn't see
before. Perhaps `UObject::CanCheckDefaultSubObjects` should use a config
variable to decide if checks should be performed, instead of using
LogCheckSubobjects log level, as this would allow the global log level to be
set without unintended side effects.


## Other Reports of this Issue

- https://answers.unrealengine.com/questions/968502/packaging-error-archetype-is-not-the-cdo-nor-a-def.html
- https://issues.unrealengine.com/issue/UE-30888
