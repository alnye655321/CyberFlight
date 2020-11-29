// Copyright 2020 NyeDigital


#include "Bots/AI/Npc/Tasks/BTTask_EnterTaxi.h"
#include "Bots/AI/Npc/NpcAIController.h"
#include "Bots/Lucy.h"
#include "Kismet/KismetMathLibrary.h"
#include <Kismet/GameplayStatics.h>
#include <Animation/AnimInstance.h>
#include "Bots/TaxiBotTarget.h"

UBTTask_EnterTaxi::UBTTask_EnterTaxi()
{
	bCreateNodeInstance = true;
	bNotifyTick = true;
	Alpha = 0.0f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> MyMontageObj(TEXT("/Game/AnimStarterPack/Montages/Mon_EnterTaxiLeft"));
	MyMontage = MyMontageObj.Object;
}

EBTNodeResult::Type UBTTask_EnterTaxi::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	MyController = Cast<ANpcAIController>(OwnerComp.GetAIOwner());
	MyLucy = Cast<ALucy>(MyController->GetPawn());

	MyLucy->CylinderComp->SetVisibility(false);

	TArray <UActorComponent*> TestComps = MyLucy->TaxiRef->GetComponentsByTag(UStaticMeshComponent::StaticClass(), TEXT("LeftDoorTarget"));

	if (TestComps.Num() > 0)
	{
		LeftDoorTarget = Cast<UStaticMeshComponent>(TestComps[0]); //there will only be one LeftDoorTarget
		UE_LOG(LogTemp, Log, TEXT("Found Tagged Comp!"));
	}

	MyLucy->SetActorEnableCollision(false);
	MyLucy->GetChoosenTaxiBotTarget()->CylinderComp->SetVisibility(false);
	

	MyLucy->SetActorRotation(LeftDoorTarget->GetComponentRotation());

	StartingLocation = MyLucy->GetActorLocation();
	FVector CompLocation = LeftDoorTarget->GetComponentLocation();

	EndingLocation.X = CompLocation.X;
	EndingLocation.Y = CompLocation.Y;
	EndingLocation.Z = StartingLocation.Z;


	return EBTNodeResult::InProgress;

}


void UBTTask_EnterTaxi::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	Alpha += DeltaSeconds * .1f;
	UE_LOG(LogTemp, Log, TEXT("Alpha, %f "), Alpha);

	if (MyLucy && Alpha <= 1 && EndingLocation.Size() > 0)
	{
		FVector NewLocation = FMath::Lerp(StartingLocation, EndingLocation, Alpha);
		
		MyLucy->SetActorLocation(NewLocation);
	}
	else
	{
		UAnimInstance* AnimInst = MyLucy->GetMesh()->GetAnimInstance();
		if (AnimInst)
		{
			FRotator NewRotation = MyLucy->GetActorRotation();
			NewRotation.Yaw = NewRotation.Yaw - 90.0f;
			MyLucy->SetActorRotation(NewRotation);
			
			AnimInst->Montage_Play(MyMontage); //entering taxi and sitting down loop
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules::KeepWorldTransform;
			AttachmentRules.bWeldSimulatedBodies = true;

			MyLucy->AttachToComponent(LeftDoorTarget, AttachmentRules); //attach to sitting target in taxi

			//find a destination and turn on the cylinder marker
			ATaxiBotTarget* MyTaxiBotTarget = MyController->FindATaxiBotTargetDestination();
			MyLucy->SetChoosenTaxiBotTarget(MyTaxiBotTarget);
			MyTaxiBotTarget->CylinderComp->SetVisibility(true);

			UE_LOG(LogTemp, Log, TEXT("Move on to different task!!!"));
			MyController->SetWalkerStatus(TEXT("TaxiRiding")); //Exiting this Task, launching BTService_TaxiRiding
		}
		
	}

	//UE_LOG(LogTemp, Log, TEXT("Enter Taxi Ticking!!!"));


}
