# Inconsistent AActor::TornOff Behavior

AActor::TornOff has inconsistent behavior depending on a) whether the
replication graph is used and b) whether the actor is destroyed with
SetLifeSpan or not.

## Scenario 1: TornOff called once (immediately after TearOff) if SetLifeSpan(0) called when using replication graph

1. Open NewMap
2. In console, run:
    
    ExampleActorLifeSpan 0
    Net.RepDriver.Enable 1

3. Run PIE.


## Scenario 2: TornOff called twiced (immediately after TearOff and again after Destroy) if SetLifeSpan(2) called when using replication graph

1. Open NewMap
2. In console, run:
    
    ExampleActorLifeSpan 2
    Net.RepDriver.Enable 1

3. Run PIE.

## Scenario 3: TornOff never called if SetLifeSpan(0) and NOT using replication graph

1. Open NewMap
2. In console, run:
    
    ExampleActorLifeSpan 0
    Net.RepDriver.Enable 0

3. Run PIE.

## Scenario 4: TornOff called once (after destroyed) if SetLifeSpan(2) and NOT using replication graph

1. Open NewMap
2. In console, run:
    
    ExampleActorLifeSpan 2
    Net.RepDriver.Enable 0

3. Run PIE.

