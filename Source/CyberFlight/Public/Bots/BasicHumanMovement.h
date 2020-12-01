// Copyright 2020 NyeDigital

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BasicHumanMovement.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UBasicHumanMovement : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CYBERFLIGHT_API IBasicHumanMovement
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Sitting)
		float SitDownWithLoop();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Walking)
		float WalkForwardWithLoop();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Standing)
		float StandingIdleWithLoop();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Taxi)
		float EnterTaxiLeft();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Taxi)
		float ExitTaxiLeft();
};
