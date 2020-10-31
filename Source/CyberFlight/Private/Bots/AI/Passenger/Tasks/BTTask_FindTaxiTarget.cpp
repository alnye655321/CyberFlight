// Copyright 2020 NyeDigital


#include "Bots/AI/Passenger/Tasks/BTTask_FindTaxiTarget.h"
#include "Bots/TaxiBotTarget.h"
#include <Kismet/GameplayStatics.h>

UBTTask_FindTaxiTarget::UBTTask_FindTaxiTarget()
{

}

EBTNodeResult::Type UBTTask_FindTaxiTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	MyController = Cast<APassengerAIController>(OwnerComp.GetAIOwner());
	MyLucy = Cast<ALucy>(MyController->GetPawn());


	TArray<AActor*> TaxiBotTargets;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATaxiBotTarget::StaticClass(), TaxiBotTargets);
	TArray<AActor*> SortedTaxiBotTargets = MyController->SortedActorsByDistance(MyLucy->GetActorLocation(), TaxiBotTargets);

	if (SortedTaxiBotTargets.Num() == 0)
	{
		return EBTNodeResult::Failed;
	}

	UE_LOG(LogTemp, Log, TEXT("Found Taxi Bot Targets! Moving to nearest."));

	MyController->SetTargetActor(SortedTaxiBotTargets[0]);
	ATaxiBotTarget* TargetTaxiBotTarget = Cast<ATaxiBotTarget>(SortedTaxiBotTargets[0]);
	TargetTaxiBotTarget->CylinderComp->SetVisibility(true);
	MyLucy->SetChoosenTaxiBotTarget(TargetTaxiBotTarget);

	MyController->SetWalkerStatus(TEXT("WaitForTaxi")); //will also trigger start of BTService_TaxiWaiting
	return EBTNodeResult::Succeeded;

}
