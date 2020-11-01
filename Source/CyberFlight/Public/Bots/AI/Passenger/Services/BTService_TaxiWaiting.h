// Copyright 2020 NyeDigital

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Bots/AI/Passenger/PassengerAIController.h"
#include "Bots/Lucy.h"
#include "BTService_TaxiWaiting.generated.h"

/**
 * 
 */
UCLASS()
class CYBERFLIGHT_API UBTService_TaxiWaiting : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTService_TaxiWaiting();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	APassengerAIController* MyController;
	ALucy* MyLucy;
	
};
