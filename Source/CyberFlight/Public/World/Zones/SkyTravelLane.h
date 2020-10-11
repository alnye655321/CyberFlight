// Copyright 2020 NyeDigital

#pragma once

#include "CoreMinimal.h"
#include "World/Zones/Zone.h"
#include "SkyTravelLane.generated.h"

/**
 * 
 */
UCLASS()
class CYBERFLIGHT_API ASkyTravelLane : public AZone
{
	GENERATED_BODY()

public:
	ASkyTravelLane();

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
		UShapeComponent* SkyLaneEntrance;

	UPROPERTY(EditAnywhere)
		UShapeComponent* SkyLaneExit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		bool HasExitLeftTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		bool HasExitRighttTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		bool UpperLevel;

	
};
