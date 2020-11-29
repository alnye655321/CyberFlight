// Copyright 2020 NyeDigital

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Bots/AI/Npc/NpcAIController.h"
#include "Bots/Lucy.h"
#include <Animation/AnimMontage.h>
#include "BTTask_EnterTaxi.generated.h"

/**
 * 
 */
UCLASS()
class CYBERFLIGHT_API UBTTask_EnterTaxi : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_EnterTaxi();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


public:

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	UPROPERTY()
		UAnimMontage* MyMontage;
	

private:
	ANpcAIController* MyController;
	ALucy* MyLucy;
	FTimerHandle StopIdleTimerHandle;
	FTimerHandle ForceTimerHandle;
	UStaticMeshComponent* LeftDoorTarget;
	FRotator StartingRotation;
	FVector StartingLocation;
	FRotator EndingRotation;
	FVector EndingLocation;
	float Alpha;
	
};
