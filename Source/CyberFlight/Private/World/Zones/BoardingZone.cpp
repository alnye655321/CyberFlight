// Copyright 2020 NyeDigital


#include "World/Zones/BoardingZone.h"
#include "World/CyberGameMode.h"
#include "Vehicle/Heli.h"
#include "Bots/Lucy.h"
#include "Bots/AI/Passenger/PassengerAIController.h"
#include "Components/BoxComponent.h"

ABoardingZone::ABoardingZone()
{
}

void ABoardingZone::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABoardingZone::OnBoxOverlap); // on the overlap
}

void ABoardingZone::OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHeli* HeliTest = Cast<AHeli>(OtherActor);
	if (HeliTest)
	{
		ACyberGameMode* CyberGameMode = Cast<ACyberGameMode>(GetWorld()->GetAuthGameMode());
		if (this->LandingZone && CyberGameMode->GetPersonTransportMissionActive())
		{
			SetCheckLanding(true);

			//https://answers.unrealengine.com/questions/165678/using-settimer-on-a-function-with-parameters.html

			FTimerDelegate TimerDel; //predefine delegate to use with parameters
			TimerDel.BindUFunction(this, FName("LandingCheckRepeating"), HeliTest);
			// Call RepeatingFunction once per second, starting two seconds from now.
			GetWorld()->GetTimerManager().SetTimer(LandingTimerHandle, TimerDel, 1.0f, true, 2.0f);
			
			//without predefining delegate - works in methods without parameters
			//GetWorldTimerManager().SetTimer(LandingTimerHandle, this, &ABoardingZone::LandingCheckRepeating(), 1.0f, true, 2.0f);

			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "transport mission is active");
		}

		if (!this->LandingZone && CyberGameMode->GetPersonTransportMissionActive())
		{
			SetCheckBoarding(true);

			FTimerDelegate TimerDel; //predefine delegate to use with parameters
			TimerDel.BindUFunction(this, FName("BoardingCheckRepeating"), HeliTest);
			GetWorld()->GetTimerManager().SetTimer(BoardingTimerHandle, TimerDel, 1.0f, true, 2.0f);

		}
	}
}

void ABoardingZone::LandingCheckRepeating(AHeli* Heli)
{
	if (GetCheckLanding())
	{
		if (Heli->GetBackDoorOpened() && !Heli->GetEngineActive())
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "transport mission has completed success!");
			SetCheckLanding(false);
			GetWorldTimerManager().ClearTimer(LandingTimerHandle);

			TArray<AActor*> ActorsAttachedToHeli;
			Heli->GetAttachedActors(ActorsAttachedToHeli);

			for (int32 i = 0; i < ActorsAttachedToHeli.Num(); i++)
			{
				UE_LOG(LogTemp, Log, TEXT("Lucy Overlaps Box: %s"), *GetNameSafe(ActorsAttachedToHeli[i]));
				ALucy* LucyBotTest = Cast<ALucy>(ActorsAttachedToHeli[i]);
				if (LucyBotTest)
				{
					APassengerAIController* AIController = Cast<APassengerAIController>(LucyBotTest->GetController());
					if (AIController)
					{
						FString BoardingStatusStr = FString(TEXT("ExitHeli"));
						AIController->SetBoardingStatus(BoardingStatusStr);
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Exiting Heli");
					}
				}
			}
		}
	}
	else
	{
		// Once we've called this function enough times, clear the Timer.
		// LandingTimerHandle can now be reused for any other Timer.
		GetWorldTimerManager().ClearTimer(LandingTimerHandle);
	}
}

void ABoardingZone::BoardingCheckRepeating(AHeli* Heli)
{
	if (GetCheckBoarding())
	{
		if (Heli->GetBackDoorOpened() && !Heli->GetEngineActive())
		{
			TArray<AActor*> Overlaps;
			this->GetOverlappingActors(Overlaps, ALucy::StaticClass());

			for (int32 i = 0; i < Overlaps.Num(); i++)
			{
				ALucy* LucyBotTest = Cast<ALucy>(Overlaps[i]);
				if (LucyBotTest)
				{
					APassengerAIController* AIController = Cast<APassengerAIController>(LucyBotTest->GetController());
					if (AIController)
					{
						FString BoardingStatusStr = FString(TEXT("MoveIntoHeli"));
						AIController->SetBoardingStatus(BoardingStatusStr);
						UE_LOG(LogTemp, Log, TEXT("Boarding has started for transport mission! Heli: %s"), *GetNameSafe(Heli));
					}
				}
			}
			
			SetCheckBoarding(false);
			GetWorldTimerManager().ClearTimer(BoardingTimerHandle);
		}
	}
	else
	{
		// Once we've called this function enough times, clear the Timer.
		// LandingTimerHandle can now be reused for any other Timer.
		GetWorldTimerManager().ClearTimer(BoardingTimerHandle);
	}
}

bool ABoardingZone::GetCheckLanding()
{
	return this->CheckLanding;
}

void ABoardingZone::SetCheckLanding(bool NewCheckLanding)
{
	this->CheckLanding = NewCheckLanding;
}

bool ABoardingZone::GetCheckBoarding()
{
	return this->CheckBoarding;
}

void ABoardingZone::SetCheckBoarding(bool NewCheckBoarding)
{
	this->CheckBoarding = NewCheckBoarding;
}

