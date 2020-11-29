// Copyright 2020 NyeDigital


#include "Bots/AI/Npc/Tasks/BTTask_ExitTaxi.h"
#include "Bots/AI/Npc/NpcAIController.h"
#include "Bots/Lucy.h"
#include "Kismet/KismetMathLibrary.h"
#include <Kismet/GameplayStatics.h>
#include <Animation/AnimInstance.h>
#include "World/CyberGameMode.h"

UBTTask_ExitTaxi::UBTTask_ExitTaxi()
{
	bCreateNodeInstance = true;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MyMontageObj(TEXT("/Game/AnimStarterPack/Montages/Mon_ExitTaxiLeft"));
	MyMontage = MyMontageObj.Object;

}

EBTNodeResult::Type UBTTask_ExitTaxi::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	MyController = Cast<ANpcAIController>(OwnerComp.GetAIOwner());
	MyLucy = Cast<ALucy>(MyController->GetPawn());

	FDetachmentTransformRules DetachmentRules = FDetachmentTransformRules::KeepWorldTransform;
	DetachmentRules.bCallModify = false;

	MyLucy->DetachFromActor(DetachmentRules);

	UAnimInstance* AnimInst = MyLucy->GetMesh()->GetAnimInstance();
	if (AnimInst)
	{
		AnimInst->Montage_Play(MyMontage); //exiting taxi and Walking a few steps forward
	}

	FTimerDelegate TimerDel; //predefine delegate to use with parameters
	TimerDel.BindUFunction(this, FName("StopExitMontage"));
	MyLucy->GetWorld()->GetTimerManager().SetTimer(StopIdleTimerHandle, TimerDel, 5.7f, false, -1.0f);

	return EBTNodeResult::InProgress;

}

void UBTTask_ExitTaxi::StopExitMontage()
{
	UE_LOG(LogTemp, Log, TEXT("Stopping Exit Montage!!!"));
	MyLucy->StopAnimMontage();
	MyLucy->SetActorEnableCollision(true);

	ACyberGameMode* CyberGameMode = Cast<ACyberGameMode>(GetWorld()->GetAuthGameMode());
	CyberGameMode->StopTaxiTransport(true);

	MyController->SetWalkerStatus(TEXT("Idle"));

}

//void UBTTask_ExitTaxi::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
//{
//
//}
