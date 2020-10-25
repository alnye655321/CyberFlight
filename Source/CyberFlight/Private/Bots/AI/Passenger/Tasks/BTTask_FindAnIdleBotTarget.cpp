// Copyright 2020 NyeDigital


#include "Bots/AI/Passenger/Tasks/BTTask_FindAnIdleBotTarget.h"
#include "Bots/Lucy.h"
#include "Bots/IdleBotTarget.h"
#include "Bots/AI/Passenger/PassengerAIController.h"
#include "MyTestActor.h"
#include <CollisionShape.h>
#include <CollisionQueryParams.h>
#include "DrawDebugHelpers.h"
#include <Engine.h>

UBTTask_FindAnIdleBotTarget::UBTTask_FindAnIdleBotTarget()
{

}

EBTNodeResult::Type UBTTask_FindAnIdleBotTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	MyController = Cast<APassengerAIController>(OwnerComp.GetAIOwner());
	MyLucy = Cast<ALucy>(MyController->GetPawn());


	TArray<AActor*> AllIdleBotActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIdleBotTarget::StaticClass(), AllIdleBotActors);
	TArray<AActor*> SortedIdleBotTargets = MyController->SortedActorsByDistance(MyLucy->GetActorLocation(), AllIdleBotActors);

	if (SortedIdleBotTargets.Num() == 0)
	{
		return EBTNodeResult::Failed;
	}

	UE_LOG(LogTemp, Log, TEXT("Found Idle Bot Targets!"));

	if (SortedIdleBotTargets.Num() > 6)
	{
		int TargetIndex = FMath::RandRange(0, 6);
		MyController->SetTargetActor(SortedIdleBotTargets[TargetIndex]);
	}
	else
	{
		MyController->SetTargetActor(SortedIdleBotTargets[0]);
	}

	MyController->SetWalkerStatus(TEXT("Idle"));
	return EBTNodeResult::Succeeded;



	
	
}
