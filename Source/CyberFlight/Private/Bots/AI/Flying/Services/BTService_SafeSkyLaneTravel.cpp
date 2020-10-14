// Copyright 2020 NyeDigital


#include "Bots/AI/Flying/Services/BTService_SafeSkyLaneTravel.h"
#include "Bots/AI/Flying/FlyingBot.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathVectorCommon.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include <Engine.h>
#include <CollisionShape.h>

UBTService_SafeSkyLaneTravel::UBTService_SafeSkyLaneTravel()
{
	bCreateNodeInstance = true; // create new nodes
	N = 1; //counting executions for alternating between positioned  Line Traces
	HitN = 1;
}

void UBTService_SafeSkyLaneTravel::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//UE_LOG(LogTemp, Log, TEXT("Sky Safe Service Running!"));
	MyController = Cast<AFlyingAIController>(OwnerComp.GetAIOwner());
	MyFlyingBot = Cast<AFlyingBot>(MyController->GetPawn());

	bool HitABot = false;

	float RandY = FMath::RandRange(-150.0f, 150.0f);
	float RnadZ = FMath::RandRange(-150.0f, 150.0f);

	//alternate position of traces to get a more complete picture of area in front
	Start = MyFlyingBot->GetActorLocation() + FVector(0.0f, RandY, RnadZ);
	End = Start + (MyFlyingBot->GetActorForwardVector() * 3000.0f);

	FHitResult Hit(ForceInit);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(MyFlyingBot);

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.1f, false, 4.f);
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldDynamic, CollisionParams);

	if (Hit.GetActor())
	{
		AFlyingBot* TestFlyingBot = Cast<AFlyingBot>(Hit.GetActor());

		if (TestFlyingBot)
		{
			HitABot = true;
			UE_LOG(LogTemp, Log, TEXT("Hit Another Bot!"));
		}
	}


	if (HitABot)
	{
		MyFlyingBot->GetCapsuleComponent()->SetLinearDamping(10.0f); //#Change Increasing Linear Damping for a slowdown upon sensing another car
		MyController->SetAllowAcceleration(false);
		HitN = N;
	}
	else if (!MyController->GetAllowAcceleration() && N > (HitN + 600)) //#TODO - ticks here should change to a timer
	{
		MyFlyingBot->GetCapsuleComponent()->SetLinearDamping(2.0f); //Reset to default on resuming acceleration
		MyController->SetAllowAcceleration(true);
	}
	N++;


}