// Copyright 2020 NyeDigital


#include "Bots/AI/Npc/NpcAIController.h"
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
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include <Engine.h>
#include "Bots/TaxiBotTarget.h"
#include <Logging/LogMacros.h>


ANpcAIController::ANpcAIController()
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
	BoardingStatusKeyName = "BoardingStatus";
	WalkerKeyName = "Walker";
	WalkerStatusKeyName = "WalkerStatus";
	HeliRiderKeyName = "HeliRider";
	HeliRiderStatusKeyName = "HeliRiderStatus";
	WaitTimeKeyName = "WaitTime";


	/* Initializes PlayerState so we can assign a team index to AI */
	bWantsPlayerState = true;

}

void ANpcAIController::OnPossess(class APawn* InPawn)
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


		//using default values of LucyBots in level to tigger these actions
		//these are values for starting the game / testing with, should not be assigned during play
		//all play assignments should occur through AI controller
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

		if (LucyBot->Walker)
		{
			SetWalker(true);
			SetWalkerStatus(TEXT("FindingIdleBotTarget"));
		}
		
		//SetHeliRiding(true); //#TODO testing, remove
		//SetHeliRidingStatus(TEXT("Init")); //#TODO testing, remove

	}
}


void ANpcAIController::OnUnPossess()
{
	Super::OnUnPossess();

	/* Stop any behavior running as we no longer have a pawn to control */
	BehaviorComp->StopTree();
}

TArray<AActor*> ANpcAIController::SortedActorsByDistance(FVector StartingLocation, TArray<AActor*> MyActors)
{

	MyActors.Sort([StartingLocation](AActor& A, AActor& B) {
		AActor* Y = &A;
		AActor* Z = &B;
		return (Y->GetActorLocation() - StartingLocation).SizeSquared()
			< (Z->GetActorLocation() - StartingLocation).SizeSquared();
		});

	return MyActors;

}

ATaxiBotTarget* ANpcAIController::FindATaxiBotTargetDestination()
{
	TArray<AActor*> TaxiBotTargets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATaxiBotTarget::StaticClass(), TaxiBotTargets);
	TArray<AActor*> SortedTaxiBotTargets = SortedActorsByDistance(LucyBot->GetActorLocation(), TaxiBotTargets);

	int RandIndex = FMath::RandRange(2, TaxiBotTargets.Num() - 1);

	ATaxiBotTarget* MyTaxiBotTarget = Cast<ATaxiBotTarget>(TaxiBotTargets[RandIndex]);

	return MyTaxiBotTarget;
}

AActor* ANpcAIController::GetTargetActor()
{
	return nullptr;
}

void ANpcAIController::SetTargetActor(AActor* NewTargetActor)
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

AActor* ANpcAIController::GetSelfActor()
{
	return nullptr;
}

void ANpcAIController::SetSelfActor(AActor* NewSelfActor)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(SelfActorKeyName, NewSelfActor);
	}
}

AActor* ANpcAIController::GetHeliRef()
{
	return nullptr;
}

void ANpcAIController::SetHeliRef(AActor* NewHeliActor)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(HeliRefKeyName, NewHeliActor);
	}
}

bool ANpcAIController::GetStop()
{
	return nullptr;
}

void ANpcAIController::SetStop(bool NewStop)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(StopKeyName, NewStop);
	}
}

bool ANpcAIController::GetRescue()
{
	return nullptr;
}

void ANpcAIController::SetRescue(bool NewRescue)
{
	if (BlackboardComp)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARescueZone::StaticClass(), FoundActors);
		AActor* ClosestRescueZone = GetClosestActorOfClass(FoundActors, LucyBot->GetActorLocation());
		UE_LOG(LogTemp, Log, TEXT("Close Rescue Zone:  %s  --- Exists"), *GetNameSafe(ClosestRescueZone));


		ABotTarget* BotTarget = Cast<ABotTarget>(LucyBot->TargetActor); //#TODO hard coded as instance on BP, need to have something more dynamic as a target

		if (ClosestRescueZone && BotTarget)
		{
			SetTargetActor(BotTarget); //next target for move to
			BlackboardComp->SetValueAsBool(RescueKeyName, NewRescue); //trigger AI rescue logic to begin
		}

	}
}

bool ANpcAIController::GetBoarding()
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

void ANpcAIController::SetBoarding(bool NewBoarding)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(BoardingKeyName, NewBoarding);
	}
}

bool ANpcAIController::GetClimbing()
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

void ANpcAIController::SetClimbing(bool NewClimbing)
{
	
	if (BlackboardComp)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALadder::StaticClass(), FoundActors);
		AActor* ClosestLadder = GetClosestActorOfClass(FoundActors, LucyBot->GetActorLocation());

		if (ClosestLadder)
		{
			SetTargetActor(ClosestLadder); //next target for move to			
			BlackboardComp->SetValueAsBool(ClimbingKeyName, NewClimbing);
		}

		
	}
}

bool ANpcAIController::GetGrappling()
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

void ANpcAIController::SetGrappling(bool NewGrappling)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(GrapplingKeyName, NewGrappling);
	}
}

FString ANpcAIController::GetBoardingStatus()
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsString(BoardingStatusKeyName);
	}
	else
	{
		return "";
	}
}

void ANpcAIController::SetBoardingStatus(FString NewBoardingStatus)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsString(BoardingStatusKeyName, NewBoardingStatus);
	}
}

bool ANpcAIController::GetWalker()
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsBool(WalkerKeyName);
	}
	else
	{
		return nullptr;
	}
}

void ANpcAIController::SetWalker(bool NewWalker)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(WalkerKeyName, NewWalker);
	}
}

FString ANpcAIController::GetWalkerStatus()
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsString(WalkerStatusKeyName);
	}
	else
	{
		return "";
	}

}

void ANpcAIController::SetWalkerStatus(FString NewWalkerStatus)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsString(WalkerStatusKeyName, NewWalkerStatus);
	}
}

bool ANpcAIController::GetHeliRiding()
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsBool(HeliRiderKeyName);
	}
	else
	{
		return nullptr;
	}
}

void ANpcAIController::SetHeliRiding(bool NewHeliRiding)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(HeliRiderKeyName, NewHeliRiding);
	}
}

FString ANpcAIController::GetHeliRidingStatus()
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsString(HeliRiderStatusKeyName);
	}
	else
	{
		return "";
	}

}

void ANpcAIController::SetHeliRidingStatus(FString NewHeliRidingStatus)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsString(HeliRiderStatusKeyName, NewHeliRidingStatus);
	}
}

float ANpcAIController::GetWaitTime()
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsFloat(WaitTimeKeyName);
	}
	else
	{
		return -1.0f;
	}
}

void ANpcAIController::SetWaitTime(float NewWaitTime)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsFloat(WaitTimeKeyName, NewWaitTime);
	}
}

