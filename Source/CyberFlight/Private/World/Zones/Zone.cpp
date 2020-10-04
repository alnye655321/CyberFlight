// Copyright 2020 NyeDigital


#include "World/Zones/Zone.h"
#include "Components/BoxComponent.h"

// Sets default values
AZone::AZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ZoneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ZoneRoot")); // initialize a component
	RootComponent = ZoneRoot; // set the root component --> Collision primitive that defines the transform (location, rotation, scale) of this Actor

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	CollisionBox->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	CollisionBox->SetGenerateOverlapEvents(true); // set overlap events to true	
	CollisionBox->AttachToComponent(ZoneRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component

}

// Called when the game starts or when spawned
void AZone::BeginPlay()
{
	Super::BeginPlay();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "my log2");
}

// Called every frame
void AZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



