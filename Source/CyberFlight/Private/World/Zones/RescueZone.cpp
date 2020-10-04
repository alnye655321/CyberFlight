// Copyright 2020 NyeDigital


#include "World/Zones/RescueZone.h"
#include "Components/BoxComponent.h"

ARescueZone::ARescueZone()
{
}



void ARescueZone::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "RescueZoneBegin");

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ARescueZone::OnBoxOverlap); // on the overlap

	//TSet<AActor*> OverlappingPawns;
	//GetOverlappingActors(OverlappingPawns, AShooterCharacter::StaticClass());

	//for (AActor* OverlappingPawn : OverlappingPawns)
	//{
	//	PickupOnTouch(CastChecked<AShooterCharacter>(OverlappingPawn));
	//}

}

void ARescueZone::OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "RescueZoneOverlap: " + OtherActor->GetName());
	}
	
}
