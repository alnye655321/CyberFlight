// Copyright 2020 NyeDigital

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Bots/AI/Npc/NpcAIController.h"
#include "Bots/Lucy.h"
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


private:
	ANpcAIController* MyController;
	ALucy* MyLucy;
	FTimerHandle StopIdleTimerHandle;



};
