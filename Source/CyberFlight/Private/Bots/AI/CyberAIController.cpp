// Copyright 2020 NyeDigital


#include "Bots/AI/CyberAIController.h"

AActor* ACyberAIController::GetClosestActorOfClass(TArray<AActor*> FoundActors, FVector OriginSearchLocation)
{
	float BestDistSq = MAX_FLT;
	AActor* NearestActor = NULL;

	if (FoundActors.Num() > 0)
	{
		for (AActor* FoundActor : FoundActors)
		{
			if (FoundActor)
			{
				const float DistSq = (FoundActor->GetActorLocation() - OriginSearchLocation).SizeSquared();
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