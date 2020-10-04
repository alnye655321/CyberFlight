// Copyright 2020 NyeDigital


#include "Bots/AI/Passenger/PassengerAIController.h"
#include "Bots/Lucy.h"
#include "Bots/BotTarget.h"
#include "Vehicle/CannonTarget.h"
#include "World/Zones/RescueZone.h"
#include "World/Interaction/Ladder.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include <Engine.h>


APassengerAIController::APassengerAIController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	/* Match with the AI Blackboard */
	TargetActorKeyName = "TargetActor";
	SelfActorKeyName = "SelfActor";
	HeliRefKeyName = "HeliRef";
	StopKeyName = "Stop";
	RescueKeyName = "Rescue";
	BoardingKeyName = "Boarding";
	ClimbingKeyName = "Climbing";
	GrapplingKeyName = "Grappling";


	/* Initializes PlayerState so we can assign a team index to AI */
	bWantsPlayerState = true;

}

void APassengerAIController::OnPossess(class APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Log, TEXT("AI Controller Online"));

	LucyBot = Cast<ALucy>(InPawn);
	if (LucyBot)
	{
		if (ensure(LucyBot->BehaviorTree->BlackboardAsset))
		{
			BlackboardComp->InitializeBlackboard(*LucyBot->BehaviorTree->BlackboardAsset);
		}

		BehaviorComp->StartTree(*LucyBot->BehaviorTree);
		UE_LOG(LogTemp, Log, TEXT("Behavior Tree Started"));


		//using default values of LucyBots in level to tragger these actions
		if (LucyBot->Rescue)
		{
			SetRescue(true);
		}

		if (LucyBot->Boarding)
		{
			SetBoarding(true);
		}

		if (LucyBot->Climbing)
		{
			SetClimbing(true);
		}

		if (LucyBot->TargetActor)
		{
			SetTargetActor(LucyBot->TargetActor);
		}
				

	}
}


void APassengerAIController::OnUnPossess()
{
	Super::OnUnPossess();

	/* Stop any behavior running as we no longer have a pawn to control */
	BehaviorComp->StopTree();
}

AActor* APassengerAIController::GetClosestActorOfClass(TArray<AActor*> FoundActors)
{
	const FVector MyLoc = LucyBot->GetActorLocation();
	float BestDistSq = MAX_FLT;
	AActor* NearestActor = NULL;

	if (FoundActors.Num() > 0)
	{
		for (AActor* FoundActor : FoundActors)
		{
			if (FoundActor)
			{
				const float DistSq = (FoundActor->GetActorLocation() - MyLoc).SizeSquared();
				if (DistSq < BestDistSq)
				{
					BestDistSq = DistSq;
					NearestActor = FoundActor;
				}
			}
		}

		UE_LOG(LogTemp, Log, TEXT("Best Actor:  %s  --- Exists"), *GetNameSafe(NearestActor));
	}
	return NearestActor;
}

AActor* APassengerAIController::GetTargetActor()
{
	return nullptr;
}

void APassengerAIController::SetTargetActor(AActor* NewTargetActor)
{
	//TArray<AActor*> FoundActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABotTarget::StaticClass(), FoundActors);
	//ABotTarget* BotTarget = Cast<ABotTarget>(FoundActors.Last());

	//if (BotTarget)
	//{
	//	SetTargetActor(BotTarget);
	//}

	if (BlackboardComp)
	{
		LucyBot->TargetActor = NewTargetActor;
		BlackboardComp->SetValueAsObject(TargetActorKeyName, NewTargetActor);
	}
}

AActor* APassengerAIController::GetSelfActor()
{
	return nullptr;
}

void APassengerAIController::SetSelfActor(AActor* NewSelfActor)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(SelfActorKeyName, NewSelfActor);
	}
}

AActor* APassengerAIController::GetHeliRef()
{
	return nullptr;
}

void APassengerAIController::SetHeliRef(AActor* NewHeliActor)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(HeliRefKeyName, NewHeliActor);
	}
}

bool APassengerAIController::GetStop()
{
	return nullptr;
}

void APassengerAIController::SetStop(bool NewStop)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(StopKeyName, NewStop);
	}
}

bool APassengerAIController::GetRescue()
{
	return nullptr;
}

void APassengerAIController::SetRescue(bool NewRescue)
{
	if (BlackboardComp)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARescueZone::StaticClass(), FoundActors);
		AActor* ClosestRescueZone = GetClosestActorOfClass(FoundActors);

		if (ClosestRescueZone)
		{
			SetTargetActor(ClosestRescueZone); //next target for move to
			BlackboardComp->SetValueAsBool(RescueKeyName, NewRescue); //trigger AI rescue logic to begin
		}

		//extracted to method GetClosestActorOfClass()

		//const FVector MyLoc = LucyBot->GetActorLocation();
		//float BestDistSq = MAX_FLT;
		//ARescueZone* BestRescueZone = NULL;

		//if (FoundActors.Num() > 0)
		//{
		//	for (AActor* FoundActor : FoundActors)
		//	{
		//		ARescueZone* MyRescueZone = Cast<ARescueZone>(FoundActor);

		//		if (MyRescueZone)
		//		{
		//			const float DistSq = (MyRescueZone->GetActorLocation() - MyLoc).SizeSquared();
		//			if (DistSq < BestDistSq)
		//			{
		//				BestDistSq = DistSq;
		//				BestRescueZone = MyRescueZone;
		//			}
		//		}
		//	}

		//	UE_LOG(LogTemp, Log, TEXT("UMyClass %s Exists"), *GetNameSafe(BestRescueZone));
		//}
		//else
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("No Rescue Zones Exist"));
		//}

		//SetTargetActor(BestRescueZone); //next target for move to
		//BlackboardComp->SetValueAsBool(RescueKeyName, NewRescue); //trigger AI rescue logic to begin
	}
}

bool APassengerAIController::GetBoarding()
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsBool(BoardingKeyName);
	}
	else
	{
		return nullptr;
	}
}

void APassengerAIController::SetBoarding(bool NewBoarding)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(BoardingKeyName, NewBoarding);
	}
}

bool APassengerAIController::GetClimbing()
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsBool(ClimbingKeyName);
	}
	else
	{
		return nullptr;
	}
}

void APassengerAIController::SetClimbing(bool NewClimbing)
{
	
	if (BlackboardComp)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALadder::StaticClass(), FoundActors);
		AActor* ClosestLadder = GetClosestActorOfClass(FoundActors);

		if (ClosestLadder)
		{
			SetTargetActor(ClosestLadder); //next target for move to			
			BlackboardComp->SetValueAsBool(ClimbingKeyName, NewClimbing);
		}

		
	}
}

bool APassengerAIController::GetGrappling()
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsBool(GrapplingKeyName);
	}
	else
	{
		return nullptr;
	}	
}

void APassengerAIController::SetGrappling(bool NewGrappling)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(GrapplingKeyName, NewGrappling);
	}
}

