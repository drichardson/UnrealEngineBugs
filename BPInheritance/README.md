# BP Inheritance Default Value Bug
Revert to default on an inherited component in Blueprints causes a validation error.

## Steps to Repro

1. Open project (will prompt to build since there is C++ code)
2. In Content Browser, navigate to *C++ Classes > BPInheritance*.
3. Right Click on *MyCppActor* and select *Create Blueprint class based on MyCppActor*.
4. When new Blueprint window opens up, select the *Sphere* component.
5. In the Details panel, observe the *Reset to Defaults* yellow arrow is visible. Press it.
6. Compile Blueprint.
7. Save Blueprint.

## Result

Validation Failure notification appears and the following is logged to the Output Window:

    DataValidation: Error: /Game/MyMyCppActor contains invalid data.
    DataValidation: Error: Data validation FAILED. Files Checked: 1, Passed: 0, Failed: 1, Skipped: 0, Unable to validate: 0
