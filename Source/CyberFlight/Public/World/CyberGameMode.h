// Copyright 2020 NyeDigital

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CyberGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CYBERFLIGHT_API ACyberGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ACyberGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scores")
		int32 CompletedMissions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
		bool PersonTransportMissionActive;

	UFUNCTION(BlueprintCallable, Category = Mission)
		void StartPersonTransport(AActor* Heli);

	bool GetPersonTransportMissionActive();

	void SetPersonTransportMissionActive(bool NewPersonTransportMissionActive);
	
};
