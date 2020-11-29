// Copyright 2020 NyeDigital

#pragma once

#include "CoreMinimal.h"
#include "Bots/BotTarget.h"
#include "IdleBotTarget.generated.h"

/**
 * 
 */
UCLASS()
class CYBERFLIGHT_API AIdleBotTarget : public ABotTarget
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AIdleBotTarget();

	virtual void BeginPlay() override;
	
};
