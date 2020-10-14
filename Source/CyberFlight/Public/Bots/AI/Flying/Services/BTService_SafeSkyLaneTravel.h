// Copyright 2020 NyeDigital

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Bots/AI/Flying/FlyingBot.h"
#include "Bots/AI/Flying/FlyingAIController.h"
#include "BTService_SafeSkyLaneTravel.generated.h"

/**
 * 
 */
UCLASS()
class CYBERFLIGHT_API UBTService_SafeSkyLaneTravel : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTService_SafeSkyLaneTravel();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UFUNCTION()
		void DelayAfterSensingCollision(AFlyingAIController* AIController);

private:

	AFlyingAIController* MyController;
	AFlyingBot* MyFlyingBot;
	FVector Start;
	FVector End;
	FTimerHandle SkyLaneTravelTimerHandle;
	FTimerDelegate TimerDel; //predefine delegate to use with parameters
	
};
