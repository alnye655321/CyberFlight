// Copyright 2020 NyeDigital

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Bots/AI/Passenger/PassengerAIController.h"
#include "Bots/Lucy.h"
#include "BTTask_IdleInPlace.generated.h"

/**
 * 
 */
UCLASS()
class CYBERFLIGHT_API UBTTask_IdleInPlace : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_IdleInPlace();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UFUNCTION()
		void StopIdleMontage();

private:
	APassengerAIController* MyController;
	ALucy* MyLucy;
	FTimerHandle StopIdleTimerHandle;
	
};
