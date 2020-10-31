// Copyright 2020 NyeDigital


#include "Bots/Lucy.h"

// Sets default values
ALucy::ALucy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CylinderComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CylinderComp"));
	CylinderComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ALucy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALucy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALucy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

AActor* ALucy::GetClosestActorOfClass(TArray<AActor*> FoundActors)
{
	const FVector MyLoc = GetActorLocation();
	float BestDistSq = MAX_FLT;
	AActor* NearestActor = NULL;

	if (FoundActors.Num() > 0)
	{
		for (AActor* FoundActor : FoundActors)
		{
			if (FoundActor)
			{
				const float DistSq = (FoundActor->GetActorLocation() - MyLoc).SizeSquared();
				if (DistSq < BestDistSq)
				{
					BestDistSq = DistSq;
					NearestActor = FoundActor;
				}
			}
		}

		UE_LOG(LogTemp, Log, TEXT("Best Actor:  %s  --- Exists"), *GetNameSafe(NearestActor));
	}
	return NearestActor;
}

ATaxiBotTarget* ALucy::GetChoosenTaxiBotTarget()
{
	return this->ChoosenTaxiBotTarget;
}

void ALucy::SetChoosenTaxiBotTarget(ATaxiBotTarget* NewTaxiBotTarget)
{
	this->ChoosenTaxiBotTarget = NewTaxiBotTarget;
}

