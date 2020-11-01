// Copyright 2020 NyeDigital


#include "Vehicle/Taxi.h"
#include <Components/StaticMeshComponent.h>

ATaxi::ATaxi()
{
	Parked = false;

	//TaxiRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RoomEntryTriggerRoot"));
	//RootComponent = TaxiRoot;

	//LeftDoorEntryTarget = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoorEntryTarget"));
	//LeftDoorEntryTarget->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	//TArray<UStaticMeshComponent> StaticComps;
	//this->GetComponents()<UStaticMeshComponent>(StaticComps);




}

//being called from blueprints BP_CR03Drivable after hover distance calculation
void ATaxi::SetParked(bool NewParked)
{
	this->Parked = NewParked;
}

bool ATaxi::GetParked()
{
	return Parked;
}

void ATaxi::BeginPlay()
{
	Super::BeginPlay();


}