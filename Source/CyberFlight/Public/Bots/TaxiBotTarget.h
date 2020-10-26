// Copyright 2020 NyeDigital

#pragma once

#include "CoreMinimal.h"
#include "Bots/BotTarget.h"
#include "TaxiBotTarget.generated.h"

/**
 * 
 */
UCLASS()
class CYBERFLIGHT_API ATaxiBotTarget : public ABotTarget
{
	GENERATED_BODY()

public:

	ATaxiBotTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
		UStaticMeshComponent* TargetComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Notification")
		UStaticMeshComponent* CylinderComp;
	
};
