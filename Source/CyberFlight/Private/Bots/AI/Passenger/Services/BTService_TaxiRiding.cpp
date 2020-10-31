// Copyright 2020 NyeDigital


#include "Bots/AI/Passenger/Services/BTService_TaxiRiding.h"
#include "Bots/AI/Passenger/PassengerAIController.h"
#include "Bots/Lucy.h"
#include "Bots/TaxiBotTarget.h"

UBTService_TaxiRiding::UBTService_TaxiRiding()
{

}

void UBTService_TaxiRiding::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	MyController = Cast<APassengerAIController>(OwnerComp.GetAIOwner());
	MyLucy = Cast<ALucy>(MyController->GetPawn());
	
	ATaxiBotTarget* MyTaxiBotTarget = MyLucy->GetChoosenTaxiBotTarget();

	//Check if we are close to the destination and on the ground
	//Parked being set from blueprints through getting HoverDistance data
	if (MyLucy->TaxiRef->GetParked()
		&& ((MyLucy->GetActorLocation() - MyTaxiBotTarget->GetActorLocation()).Size() < 2000.0))
	{
		MyTaxiBotTarget->CylinderComp->SetVisibility(false);
		MyController->SetWalkerStatus(TEXT("ExitTaxi"));
		UE_LOG(LogTemp, Log, TEXT("ExitingTaxi!!!"));
	}

}
