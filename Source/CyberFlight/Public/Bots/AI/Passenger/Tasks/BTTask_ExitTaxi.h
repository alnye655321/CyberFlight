// Copyright 2020 NyeDigital

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Bots/AI/Passenger/PassengerAIController.h"
#include "Bots/Lucy.h"
#include <Animation/AnimMontage.h>
#include "BTTask_ExitTaxi.generated.h"

/**
 * 
 */
UCLASS()
class CYBERFLIGHT_API UBTTask_ExitTaxi : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_ExitTaxi();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


public:

	//void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	UFUNCTION()
		void StopExitMontage();

	UPROPERTY()
		UAnimMontage* MyMontage;


private:
	APassengerAIController* MyController;
	ALucy* MyLucy;
	FTimerHandle StopIdleTimerHandle;



};
