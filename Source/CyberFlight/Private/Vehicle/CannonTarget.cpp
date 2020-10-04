// Copyright 2020 NyeDigital

#include "Vehicle/CannonTarget.h"
#include "Components/SphereComponent.h"

// Sets default values
ACannonTarget::ACannonTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);

	// Set as root component
	RootComponent = CollisionComp;

}

// Called when the game starts or when spawned
void ACannonTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void ACannonTarget::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//}

