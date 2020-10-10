// Copyright 2020 NyeDigital


#include "World/CyberGameMode.h"
#include "World/Zones/BoardingZone.h"
#include "Vehicle/Heli.h"
#include "Bots/Lucy.h"
#include "Bots/AI/Passenger/PassengerAIController.h"
#include <Engine.h>

ACyberGameMode::ACyberGameMode()
{
	CompletedMissions = 0;
}

void ACyberGameMode::StartPersonTransport(AActor* Heli)
{
	AHeli* HeliPawn = Cast<AHeli>(Heli);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Start Boarding Mission");

	//find a possible boarding area with NPCs waiting, according to map
	bool FoundBoardingZone = false;
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoardingZone::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0 && HeliPawn) {
		for (AActor* BoardingZoneTest : FoundActors)
		{
			ABoardingZone* BoardingZone = Cast<ABoardingZone>(BoardingZoneTest);
			if (BoardingZone && !BoardingZone->LandingZone)
			{
				TArray<AActor*> Overlaps;
				BoardingZone->GetOverlappingActors(Overlaps, ALucy::StaticClass());

				for (int32 i = 0; i < Overlaps.Num(); i++)
				{
					ALucy* LucyBotTest = Cast<ALucy>(Overlaps[i]);
					if (LucyBotTest)
					{
						APassengerAIController* AIController = Cast<APassengerAIController>(LucyBotTest->GetController());

						if (AIController)
						{
							FString BoardingStatusStr = FString(TEXT("AwaitBoarding"));

							AIController->SetBoarding(true);
							AIController->SetBoardingStatus(BoardingStatusStr);
						}

						//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TestBot->GetName()); 
						//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, AIController->GetName());
					}

				}
				FoundBoardingZone = true; //found boarding zone that isnt landing zone
				break; //stop when found first boarding area that is playable
			}
		}

		//find a landing zone for the mission
		//set the target landing zone for game mode completion if we have a valid boarding zone
		if (FoundBoardingZone)
		{
			for (AActor* BoardingZoneTest : FoundActors)
			{
				ABoardingZone* LandingZoneTest = Cast<ABoardingZone>(BoardingZoneTest);
				if (LandingZoneTest && LandingZoneTest->LandingZone)
				{
					HeliPawn->ZoneObjective = LandingZoneTest;
					SetPersonTransportMissionActive(true); //activate mission for queries on Game Mode
				}
			}
		}

	}

	
}

bool ACyberGameMode::GetPersonTransportMissionActive()
{
	return PersonTransportMissionActive;
}

void ACyberGameMode::SetPersonTransportMissionActive(bool NewPersonTransportMissionActive)
{
	this->PersonTransportMissionActive = NewPersonTransportMissionActive;
}
