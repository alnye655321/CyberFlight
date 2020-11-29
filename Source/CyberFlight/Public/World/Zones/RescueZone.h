// Copyright 2020 NyeDigital

#pragma once

#include "CoreMinimal.h"
#include "World/Zones/Zone.h"
#include "RescueZone.generated.h"

/**
 * 
 */
UCLASS()
class CYBERFLIGHT_API ARescueZone : public AZone
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	ARescueZone();

	virtual void BeginPlay() override;

	// called when player enters the box
	UFUNCTION()
		void OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
