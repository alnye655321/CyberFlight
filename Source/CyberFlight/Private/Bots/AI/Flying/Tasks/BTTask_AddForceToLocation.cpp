// Copyright 2020 NyeDigital


//#include "CyberFlight/CyberFlight.h"
#include "Bots/AI/Flying/Tasks/BTTask_AddForceToLocation.h"
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
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

UBTTask_AddForceToLocation::UBTTask_AddForceToLocation()
{
	//https://answers.unrealengine.com/questions/617725/c-bttask-finish-execute.html
	bCreateNodeInstance = true; // create new nodes, !!!important for the multiple AIs using this at once
}

EBTNodeResult::Type UBTTask_AddForceToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	MyController = Cast<AFlyingAIController>(OwnerComp.GetAIOwner());
	MyFlyingBot = Cast<AFlyingBot>(MyController->GetPawn());

	MoveToLocation = MyController->GetMoveToLocation();
	InitialDistance = GetDistanceToFinalPosition();
	DistanceTolerance = 100.0f;

    //https://answers.unrealengine.com/questions/617725/c-bttask-finish-execute.html
	AFlyingAIController* AIController = Cast<AFlyingAIController>(MyFlyingBot->GetController());
	UBehaviorTreeComponent* Tree = Cast<UBehaviorTreeComponent>(AIController->GetBrainComponent());

	//https://answers.unrealengine.com/questions/757299/view.html
	FTimerDelegate TimerDel; //predefine delegate to use with parameters
	TimerDel.BindUFunction(this, FName("ApplyForceRepeating"), MyFlyingBot, Tree);
	MyFlyingBot->GetWorld()->GetTimerManager().SetTimer(ForceTimerHandle, TimerDel, 0.01f, true, 0.01f);
	
	return EBTNodeResult::InProgress;
}

void UBTTask_AddForceToLocation::ApplyForceRepeating(AFlyingBot* FlyingBot, UBehaviorTreeComponent* Tree)
{
	UCapsuleComponent* Capsule = MyFlyingBot->GetCapsuleComponent();
	float Velocity = Capsule->GetPhysicsLinearVelocity().Size();

	if (Velocity <= MyFlyingBot->GetFlightMaxVelocity())
	{
		Capsule->AddForce(GetForceVector(), NAME_None, true);
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("Max velocity reached!"));
		//UE_LOG(LogTemp, Log, TEXT("Sky Lane Location: %s"), *Y->SkyLaneEntrance->GetSocketLocation(TEXT("SkyLaneEntranceBox")).ToString() );
	}

	//UE_LOG(LogTemp, Log, TEXT("DistanceCheck: %f"), GetDistanceToFinalPosition());

	UpdateRotationToFaceVelocity();

	//check if completed
	if (GetDistanceToFinalPosition() <= DistanceTolerance)
	{

		UE_LOG(LogTemp, Log, TEXT("Close to destination - stopping force application"));

		if (MyController->GetMovementStatus().Equals(TEXT("MovingToExit")))
		{
			MyController->SetMovementStatus(TEXT("AtExit"));

		}
		else if (MyController->GetMovementStatus().Equals(TEXT("MovingToStart")))
		{
			MyController->SetMovementStatus(TEXT("MovingToExit"));
		}

		MyFlyingBot->GetWorld()->GetTimerManager().ClearTimer(ForceTimerHandle);
		MyController->SetAllowAcceleration(false); //will abort this task

		if (Tree)
		{
			//Tree->OnTaskFinished(this, EBTNodeResult::Succeeded);
		}
		

	}



}


FVector UBTTask_AddForceToLocation::GetForceVector()
{
	FVector UnitDirection = UKismetMathLibrary::GetDirectionUnitVector(MyFlyingBot->GetActorLocation(), MoveToLocation);
	float Alpha = (InitialDistance - GetDistanceToFinalPosition()) / InitialDistance;
	FVector MyLerp = FMath::Lerp(UnitDirection, FVector(0.0f, 0.0f, 0.0f), Alpha);

	return MyLerp * MyFlyingBot->GetFlightAcceleration();
}

float UBTTask_AddForceToLocation::GetDistanceToFinalPosition()
{
	FVector Distance = MyFlyingBot->GetActorLocation() - MoveToLocation;
	return Distance.Size();
}

void UBTTask_AddForceToLocation::UpdateRotationToFaceVelocity()
{

	FRotator RotA = MyFlyingBot->GetActorRotation();
	FRotator RotB = UKismetMathLibrary::FindLookAtRotation(MyFlyingBot->GetActorLocation(), MoveToLocation);

	FRotator MyRotator = FMath::Lerp(RotA, RotB, 0.1f); //rotation alpha can be changed here

	MyFlyingBot->SetActorRotation(MyRotator);

}