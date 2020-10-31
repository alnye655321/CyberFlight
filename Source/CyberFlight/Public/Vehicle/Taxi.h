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

	UFUNCTION(BlueprintCallable, Category = Mission)
		void SetParked(bool NewParked);

	UFUNCTION(BlueprintCallable, Category = Mission)
		bool GetParked();

	//UPROPERTY(EditAnywhere)
	//	USceneComponent* TaxiRoot;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	//	UStaticMeshComponent* LeftDoorEntryTarget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool Parked; //Parked being set from blueprints through getting HoverDistance data

};
