// Copyright 2020 NyeDigital

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Bots/AI/Flying/FlyingBot.h"
#include "Bots/AI/Flying/FlyingAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BTTask_AddForceToLocation.generated.h"

/**
 *
 */
UCLASS()
class CYBERFLIGHT_API UBTTask_AddForceToLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_AddForceToLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


public:

	UFUNCTION()
		void ApplyForceRepeating(AFlyingBot* FlyingBot, UBehaviorTreeComponent* Tree);

	FVector GetForceVector();
	float GetDistanceToFinalPosition();
	void UpdateRotationToFaceVelocity();



private:

	AFlyingAIController* MyController;
	FVector MoveToLocation;
	float InitialDistance;
	AFlyingBot* MyFlyingBot;
	FTimerHandle ForceTimerHandle;
	float DistanceTolerance;
};