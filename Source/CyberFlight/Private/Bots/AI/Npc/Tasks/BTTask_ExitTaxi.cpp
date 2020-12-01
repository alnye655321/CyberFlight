// Copyright 2020 NyeDigital


#include "Bots/AI/Npc/Tasks/BTTask_ExitTaxi.h"
#include "Bots/AI/Npc/NpcAIController.h"
#include "Bots/Lucy.h"
#include "Kismet/KismetMathLibrary.h"
#include <Kismet/GameplayStatics.h>
#include <Animation/AnimInstance.h>
#include "Bots/BasicHumanMovement.h"
#include "World/CyberGameMode.h"

UBTTask_ExitTaxi::UBTTask_ExitTaxi()
{
	bCreateNodeInstance = true;
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
		if (AnimInst->GetClass()->ImplementsInterface(UBasicHumanMovement::StaticClass()))
		{
			IBasicHumanMovement* MyBasicMovement = Cast<IBasicHumanMovement>(AnimInst);
			MyBasicMovement->Execute_ExitTaxiLeft(AnimInst);
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No Anim Instance Present!"));
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
