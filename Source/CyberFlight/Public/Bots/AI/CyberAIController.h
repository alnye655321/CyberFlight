// Copyright 2020 NyeDigital

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CyberAIController.generated.h"

/**
 * 
 */
UCLASS()
class CYBERFLIGHT_API ACyberAIController : public AAIController
{
	GENERATED_BODY()

	
public:
		AActor* GetClosestActorOfClass(TArray<AActor*> FoundActors, FVector OriginSearchLocation);
};
