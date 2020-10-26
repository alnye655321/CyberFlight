// Copyright 2020 NyeDigital

#pragma once

#include "CoreMinimal.h"
#include "Vehicle/Vehicle.h"
#include "Taxi.generated.h"

/**
 * 
 */
UCLASS()
class CYBERFLIGHT_API ATaxi : public AVehicle
{
	GENERATED_BODY()
	
public:
	ATaxi();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
