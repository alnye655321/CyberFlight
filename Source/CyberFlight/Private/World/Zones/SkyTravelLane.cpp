// Copyright 2020 NyeDigital


#include "World/Zones/SkyTravelLane.h"
#include "Components/BoxComponent.h"

ASkyTravelLane::ASkyTravelLane()
{

	SkyLaneEntrance = CreateDefaultSubobject<UBoxComponent>(TEXT("SkyLaneEntranceBox"));
	SkyLaneEntrance->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	SkyLaneEntrance->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	SkyLaneEntrance->SetGenerateOverlapEvents(true); // set overlap events to true	
	SkyLaneEntrance->AttachToComponent(ZoneRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component

	SkyLaneExit = CreateDefaultSubobject<UBoxComponent>(TEXT("SkyLaneExitBox"));
	SkyLaneExit->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // set world scale according to new vector, relative to parent root
	SkyLaneExit->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));// relative to parent root
	SkyLaneExit->SetGenerateOverlapEvents(true); // set overlap events to true	
	SkyLaneExit->AttachToComponent(ZoneRoot, FAttachmentTransformRules::KeepRelativeTransform); // attach to root component

}

void ASkyTravelLane::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASkyTravelLane::OnBoxOverlap); // on the overlap
}

void ASkyTravelLane::OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		//UE_LOG(LogTemp, Log, TEXT("Skylane Begin Overlapped Actor: %s"), *GetNameSafe(OtherActor));
	}
}
