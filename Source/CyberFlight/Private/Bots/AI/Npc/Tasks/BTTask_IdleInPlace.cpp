// Copyright 2020 NyeDigital


#include "Bots/AI/Npc/Tasks/BTTask_IdleInPlace.h"
#include "Bots/Lucy.h"
#include "Bots/IdleBotTarget.h"
#include "Bots/AI/Npc/NpcAIController.h"
#include <Animation/AnimInstance.h>

UBTTask_IdleInPlace::UBTTask_IdleInPlace()
{
	bCreateNodeInstance = true;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MyMontageObj(TEXT("/Game/AnimStarterPack/Montages/Mon_Idle4"));
	MyMontage = MyMontageObj.Object;
}

EBTNodeResult::Type UBTTask_IdleInPlace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	MyController = Cast<ANpcAIController>(OwnerComp.GetAIOwner());
	MyLucy = Cast<ALucy>(MyController->GetPawn());

	UAnimInstance* AnimInst = MyLucy->GetMesh()->GetAnimInstance();
	if (AnimInst)
	{
		AnimInst->Montage_Play(MyMontage);
	}
	//c++ blueprint implementable event, not need with direct playing above
	//MyLucy->AnimateIdleInPlace(); //Play the montage from blueprints

	float IdleTimeLength = FMath::RandRange(5.0f, 20.0f);

	FTimerDelegate TimerDel; //predefine delegate to use with parameters
	TimerDel.BindUFunction(this, FName("StopIdleMontage"));
	MyLucy->GetWorld()->GetTimerManager().SetTimer(StopIdleTimerHandle, TimerDel, IdleTimeLength, false, -1.0f);

	return EBTNodeResult::InProgress;

}

void UBTTask_IdleInPlace::StopIdleMontage()
{
	MyLucy->StopAnimMontage();
	MyController->SetWalkerStatus(TEXT("FindingIdleBotTarget"));

	UE_LOG(LogTemp, Log, TEXT("Stopping Idle Montage and Finishing Task"));
}
