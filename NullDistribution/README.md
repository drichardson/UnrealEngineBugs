# UDistributionFloat is reset to NULL on blueprint compile.

A UDistributionFloat property is reset to NULL when compiling a Blueprint sub-class of a C++
class that has a UDistributionFloat property.


## Steps to Reproduce from blank C++ project
1. Create blank C++ project
2. Add UDistributionFloat property to Game Mode Base.
3. Create a Blueprint sub-class of the project's C++ game mode base.
4. Open Blueprint in editor, and change the value of the UDistributionFloat property.
5. Compile the blueprint.

### Result
UDistributionFloat property reset to None.

### Expected Result
UDistributionFloat property not reset to None.


