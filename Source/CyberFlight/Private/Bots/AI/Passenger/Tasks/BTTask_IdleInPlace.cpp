// Copyright 2020 NyeDigital


#include "Bots/AI/Passenger/Tasks/BTTask_IdleInPlace.h"
#include "Bots/Lucy.h"
#include "Bots/IdleBotTarget.h"
#include "Bots/AI/Passenger/PassengerAIController.h"

UBTTask_IdleInPlace::UBTTask_IdleInPlace()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_IdleInPlace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	MyController = Cast<APassengerAIController>(OwnerComp.GetAIOwner());
	MyLucy = Cast<ALucy>(MyController->GetPawn());

	MyLucy->AnimateIdleInPlace(); //Play the montage from blueprints

	float IdleTimeLength = FMath::RandRange(5.0f, 20.0f);

	FTimerDelegate TimerDel; //predefine delegate to use with parameters
	TimerDel.BindUFunction(this, FName("StopIdleMontage"));
	MyLucy->GetWorld()->GetTimerManager().SetTimer(StopIdleTimerHandle, TimerDel, IdleTimeLength, false, -1.0f);

	return EBTNodeResult::InProgress;

}

void UBTTask_IdleInPlace::StopIdleMontage()
{
	UE_LOG(LogTemp, Log, TEXT("Stopping Idle Montage and Finishing Task"));
	MyController->SetWalkerStatus(TEXT("FindingIdleBotTarget"));
}
