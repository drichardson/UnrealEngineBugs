#include "MyCppActor.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

AMyCppActor::AMyCppActor()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
}
