// Copyright 2020 NyeDigital

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Bots/AI/Passenger/PassengerAIController.h"
#include "Bots/Lucy.h"
#include "BTTask_FindTaxiTarget.generated.h"

/**
 * 
 */
UCLASS()
class CYBERFLIGHT_API UBTTask_FindTaxiTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_FindTaxiTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
public:

private:
	APassengerAIController* MyController;
	ALucy* MyLucy;

};
