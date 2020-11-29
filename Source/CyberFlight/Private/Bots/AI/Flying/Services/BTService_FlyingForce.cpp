// Copyright 2020 NyeDigital


#include "Bots/AI/Flying/Services/BTService_FlyingForce.h"
#include "Bots/AI/Flying/FlyingAIController.h"
#include "Bots/AI/Flying/FlyingBot.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathVectorCommon.h"
#include "Components/CapsuleComponent.h"

/*ai controller includes*/
#include "Bots/AI/Flying/FlyingAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

UBTService_FlyingForce::UBTService_FlyingForce()
{
	bCreateNodeInstance = true; // create new nodes

}

void UBTService_FlyingForce::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{


}

