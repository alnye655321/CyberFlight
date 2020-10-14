// Copyright 2020 NyeDigital

#pragma once

#include "CoreMinimal.h"
#include "World/Zones/Zone.h"
#include "Vehicle/Heli.h"
#include "BoardingZone.generated.h"

/**
 * 
 */
UCLASS()
class CYBERFLIGHT_API ABoardingZone : public AZone
{
	GENERATED_BODY()


private:
	FTimerHandle LandingTimerHandle;
	FTimerHandle BoardingTimerHandle;
	bool CheckLanding;
	bool CheckBoarding;
	

public:
		ABoardingZone();

		virtual void BeginPlay() override;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ZoneState")
			bool LandingZone;

		UFUNCTION()
			void OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UFUNCTION()
			void LandingCheckRepeating(AHeli* Heli);

		UFUNCTION()
		void BoardingCheckRepeating(AHeli* Heli);

		bool GetCheckLanding();

		void SetCheckLanding(bool NewCheckLanding);

		bool GetCheckBoarding();

		void SetCheckBoarding(bool NewCheckBoarding);



};
