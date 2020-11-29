// Copyright 2020 NyeDigital


#include "Vehicle/Heli.h"

// Sets default values
AHeli::AHeli()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
//void AHeli::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

// Called every frame
//void AHeli::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

// Called to bind functionality to input
//void AHeli::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

AActor* AHeli::GetClosestActorOfClass(TArray<AActor*> FoundActors)
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

bool AHeli::GetEngineActive()
{
	return this->EngineActive;
}

void AHeli::SetEngineActive(bool NewEngineActive)
{
	this->EngineActive = NewEngineActive;
}

bool AHeli::GetBackDoorOpened()
{
	return this->BackDoorOpened;
}

void AHeli::SetBackDoorOpened(bool NewBackDoorOpened)
{
	this->BackDoorOpened = NewBackDoorOpened;
}

