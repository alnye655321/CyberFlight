// Copyright 2020 NyeDigital


#include "Bots/AI/Flying/FlyingAIController.h"
#include "Bots/AI/Flying/FlyingBot.h"
#include "World/Zones/SkyTravelLane.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include <Engine.h>
#include <CollisionShape.h>
#include <CollisionQueryParams.h>
#include "DrawDebugHelpers.h"


AFlyingAIController::AFlyingAIController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	/* Match with the AI Blackboard */
	TargetActorKeyName = "TargetActor";
	SelfActorKeyName = "SelfActor";
	HeliRefKeyName = "HeliRef";
	MoveToLocationKeyName = "MoveToLocation";
	CurrentSkyLaneKeyName = "CurrentSkyLane";
	AllowAccelerationKeyName = "AllowAcceleration";
	MovementStatusKeyName = "MovementStatus";


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

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASkyTravelLane::StaticClass(), FoundActors);

		AActor* ClosestSkyTravelLane = GetClosestActorOfClass(FoundActors, FlyingBot->GetActorLocation());

		if (ClosestSkyTravelLane)
		{
			SetCurrentSkyLane(ClosestSkyTravelLane);
			SetAllowAcceleration(true);
			SetMovementStatus("MovingToExit");
			UE_LOG(LogTemp, Log, TEXT("Found A SkyLane"));
		}

	}
}

void AFlyingAIController::OnUnPossess()
{
	Super::OnUnPossess();

	/* Stop any behavior running as we no longer have a pawn to control */
	BehaviorComp->StopTree();
}



FVector AFlyingAIController::FindAMoveToSkyLaneLocation()
{
	UE_LOG(LogTemp, Log, TEXT("Running FindAMoveToSkyLaneLocation"));
	ASkyTravelLane* MyCurrentSkyLane = Cast<ASkyTravelLane>(GetCurrentSkyLane());

	//TArray<AActor*> FoundSkyLanes;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASkyTravelLane::StaticClass(), FoundSkyLanes);
	//TArray<AActor*> SortedSkyLanes = SortedClosestSkyLanesByEntrance(FoundSkyLanes);

	TArray<ASkyTravelLane*> MySkyTravelLanes;
	TArray<FHitResult> OutHits;
	FVector ActorLocation = FlyingBot->GetActorLocation();
	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(4000.0f);
	DrawDebugSphere(GetWorld(), ActorLocation, MyColSphere.GetSphereRadius(), 100, FColor::Purple, false, 5); //true is persist in world, int is lifetime

	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, ActorLocation, ActorLocation, FQuat::Identity, ECC_Visibility, MyColSphere);

	if (isHit)
	{
		// loop through TArray
		for (FHitResult Hit : OutHits)
		{
			ASkyTravelLane* TestSkyTravelLane = Cast<ASkyTravelLane>(Hit.GetActor());

			if (Hit.GetComponent() && TestSkyTravelLane)
			{
				FString ComponentName = Hit.GetComponent()->GetName();
				//if ===SkyLaneEntranceBox
				//then TestSkyTravelLane to array

				if (ComponentName.Equals(FString(TEXT("SkyLaneEntranceBox"))))
				{
					MySkyTravelLanes.Add(TestSkyTravelLane);
					UE_LOG(LogTemp, Log, TEXT("Entrace: %s exists on SkyTavelLane: %s"), *ComponentName, *GetNameSafe(TestSkyTravelLane));
				}
			}
		}

		if (MySkyTravelLanes.Num() > 0)
		{
			if (MySkyTravelLanes.Num() == 1)
			{
				SetCurrentSkyLane(MySkyTravelLanes[0]);
				return MySkyTravelLanes[0]->SkyLaneEntrance->GetSocketLocation(TEXT("SkyLaneEntranceBox"));
			}
			else
			{
				int ReturnIndex = FMath::RandRange(0, MySkyTravelLanes.Num() - 1);
				UE_LOG(LogTemp, Log, TEXT("Rand Index Chosen: %d"), ReturnIndex);
				SetCurrentSkyLane(MySkyTravelLanes[ReturnIndex]);
				return MySkyTravelLanes[ReturnIndex]->SkyLaneEntrance->GetSocketLocation(TEXT("SkyLaneEntranceBox"));
			}
		}

	}

	FVector vector;
	return vector;

}

//trying to get nearest sky lane by closest start point, will be able to choose index 0 or 1 randomly for left and right turns
TArray<AActor*> AFlyingAIController::SortedClosestSkyLanesByEntrance(TArray<AActor*> FoundActors)
{
	FVector MyLoc = FlyingBot->GetActorLocation();

	FoundActors.Sort([MyLoc](AActor& A, AActor& B) {
		//AActor* Y = &A;
		//AActor* Z = &B;
		ASkyTravelLane* Y = Cast<ASkyTravelLane>(&A);
		ASkyTravelLane* Z = Cast<ASkyTravelLane>(&B);
		//UE_LOG(LogTemp, Log, TEXT("Sky Lane Location: %s"), *Y->SkyLaneEntrance->GetSocketLocation(TEXT("SkyLaneEntranceBox")).ToString() );
		//return (Y->GetActorLocation() - MyLoc).SizeSquared() < (Z->GetActorLocation() - MyLoc).SizeSquared();
		return (Y->SkyLaneEntrance->GetSocketLocation(TEXT("SkyLaneEntranceBox")) - MyLoc).SizeSquared() 
			< (Z->SkyLaneEntrance->GetSocketLocation(TEXT("SkyLaneEntranceBox")) - MyLoc).SizeSquared();
		});

	return FoundActors;
}

int AFlyingAIController::FindSkyLaneIndex(ASkyTravelLane* MySkyTravelLane)
{

	if (MySkyTravelLane->HasExitLeftTurn && MySkyTravelLane->HasExitRighttTurn)
	{
		return FMath::RandRange(0, 1); //choose a random left or right turn
	}
	else
	{
		return 0;
	}

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
	if (BlackboardComp)
	{
		AActor* Self = Cast<AActor>(BlackboardComp->GetValueAsObject(SelfActorKeyName));
		if (Self)
		{
			return Self;
		}
	}

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

AActor* AFlyingAIController::GetCurrentSkyLane()
{
	if (BlackboardComp)
	{
		ASkyTravelLane* MyCurrentSkyLane = Cast<ASkyTravelLane>(BlackboardComp->GetValueAsObject(CurrentSkyLaneKeyName));
		if (MyCurrentSkyLane)
		{
			return MyCurrentSkyLane;
		}
	}
	return nullptr;
}

void AFlyingAIController::SetCurrentSkyLane(AActor* NewCurrentSkyLane)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(CurrentSkyLaneKeyName, NewCurrentSkyLane);
	}
}

bool AFlyingAIController::GetAllowAcceleration()
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsBool(AllowAccelerationKeyName);
	}
	else
	{
		return nullptr;
	}
}

void AFlyingAIController::SetAllowAcceleration(bool NewAllowAcceleration)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(AllowAccelerationKeyName, NewAllowAcceleration);
	}
}

FString AFlyingAIController::GetMovementStatus()
{
	if (BlackboardComp)
	{
		return BlackboardComp->GetValueAsString(MovementStatusKeyName);
	}
	else
	{
		return "";
	}
}

void AFlyingAIController::SetMovementStatus(FString NewMovementStatus)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsString(MovementStatusKeyName, NewMovementStatus);
	}
}

