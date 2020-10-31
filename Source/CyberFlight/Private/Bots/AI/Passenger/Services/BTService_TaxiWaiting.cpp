// Copyright 2020 NyeDigital


#include "Bots/AI/Passenger/Services/BTService_TaxiWaiting.h"
#include "Bots/AI/Passenger/PassengerAIController.h"
#include "Bots/Lucy.h"

UBTService_TaxiWaiting::UBTService_TaxiWaiting()
{

}

void UBTService_TaxiWaiting::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//UE_LOG(LogTemp, Log, TEXT("Taxi Waiting Service Running!"));
	MyController = Cast<APassengerAIController>(OwnerComp.GetAIOwner());
	MyLucy = Cast<ALucy>(MyController->GetPawn());

	//Parked being set from blueprints through getting HoverDistance data
	if (MyLucy->TaxiRef->GetParked() 
		&& ((MyLucy->GetActorLocation() - MyLucy->TaxiRef->GetActorLocation()).Size() < 2000.0))
	{
		MyController->SetWalkerStatus(TEXT("EnterTaxi"));
		UE_LOG(LogTemp, Log, TEXT("Taxi Start Boarding!"));
	}

}
