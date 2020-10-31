// Copyright 2020 NyeDigital

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "../PassengerAIController.h"
#include "Bots/Lucy.h"
#include "BTService_TaxiRiding.generated.h"

/**
 * 
 */
UCLASS()
class CYBERFLIGHT_API UBTService_TaxiRiding : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTService_TaxiRiding();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	APassengerAIController* MyController;
	ALucy* MyLucy;
	
};
