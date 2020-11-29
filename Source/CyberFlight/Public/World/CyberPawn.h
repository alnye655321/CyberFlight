// Copyright 2020 NyeDigital

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CyberPawn.generated.h"

UCLASS()
class CYBERFLIGHT_API ACyberPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACyberPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
