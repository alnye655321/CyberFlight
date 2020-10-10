// Copyright 2020 NyeDigital


#include "Bots/AI/Flying/FlyingAIController.h"
#include "Bots/AI/Flying/FlyingBot.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include <Engine.h>


AFlyingAIController::AFlyingAIController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	/* Match with the AI Blackboard */
	TargetActorKeyName = "TargetActor";
	SelfActorKeyName = "SelfActor";
	HeliRefKeyName = "HeliRef";
	MoveToLocationKeyName = "MoveToLocation";


	/* Initializes PlayerState so we can assign a team index to AI */
	bWantsPlayerState = true;

}

void AFlyingAIController::OnPossess(class APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Log, TEXT("AI Controller Online"));

	FlyingBot = Cast<AFlyingBot>(InPawn);
	if (FlyingBot)
	{
		if (ensure(FlyingBot->BehaviorTree->BlackboardAsset))
		{
			BlackboardComp->InitializeBlackboard(*FlyingBot->BehaviorTree->BlackboardAsset);
		}

		BehaviorComp->StartTree(*FlyingBot->BehaviorTree);
		UE_LOG(LogTemp, Log, TEXT("Behavior Tree Started"));

	}
}

void AFlyingAIController::OnUnPossess()
{
	Super::OnUnPossess();

	/* Stop any behavior running as we no longer have a pawn to control */
	BehaviorComp->StopTree();
}

AActor* AFlyingAIController::GetTargetActor()
{
	return nullptr;
}

void AFlyingAIController::SetTargetActor(AActor* NewTargetActor)
{

	if (BlackboardComp)
	{
		FlyingBot->TargetActor = NewTargetActor;
		BlackboardComp->SetValueAsObject(TargetActorKeyName, NewTargetActor);
	}
}

AActor* AFlyingAIController::GetSelfActor()
{
	return nullptr;
}

void AFlyingAIController::SetSelfActor(AActor* NewSelfActor)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(SelfActorKeyName, NewSelfActor);
	}
}

AActor* AFlyingAIController::GetHeliRef()
{
	return nullptr;
}

void AFlyingAIController::SetHeliRef(AActor* NewHeliActor)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(HeliRefKeyName, NewHeliActor);
	}
}

FVector AFlyingAIController::GetMoveToLocation()
{
	FVector vector;
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsVector(MoveToLocationKeyName);
	}
	else
	{
		return vector;
	}
}

void AFlyingAIController::SetMoveToLocation(FVector NewMoveToLocation)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsVector(MoveToLocationKeyName, NewMoveToLocation);
	}
}
