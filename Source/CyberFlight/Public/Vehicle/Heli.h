// Copyright 2020 NyeDigital

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "World/Zones/Zone.h"
#include "Heli.generated.h"

UCLASS()
class CYBERFLIGHT_API AHeli : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHeli();

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	AActor* GetClosestActorOfClass(TArray<AActor*> FoundActors);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mission)
		AZone* ZoneObjective;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Engine)
		bool EngineActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Doors)
		bool BackDoorOpened;

	bool GetEngineActive();

	void SetEngineActive(bool NewEngineActive);

	bool GetBackDoorOpened();

	void SetBackDoorOpened(bool NewBackDoorOpened);




};
