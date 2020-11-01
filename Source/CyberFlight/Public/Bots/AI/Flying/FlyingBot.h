// Copyright 2020 NyeDigital

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FlyingBot.generated.h"

UCLASS()
class CYBERFLIGHT_API AFlyingBot : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFlyingBot();


	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		AActor* TargetActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Flight)
		float FlightAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Flight)
		float FlightMaxVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Flight)
		float FlightLinearDamping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Flight)
		float FlightAngularDamping;

	float GetFlightAcceleration();

	void SetFlightAcceleration(float NewFlightAcceleration);

	float GetFlightMaxVelocity();

	void SetFlightMaxVelocity(float NewFlightMaxVelocity);

	float GetFlightLinearDamping();

	void SetFlightLinearDamping(float NewFlightLinearDamping);

	float GetFlightAngularDamping();

	void SetFlightAngularDamping(float NewFlightAngularDamping);

};
