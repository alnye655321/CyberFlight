// Copyright 2020 NyeDigital


#include "Bots/AI/Flying/FlyingBot.h"

// Sets default values
AFlyingBot::AFlyingBot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlightAcceleration = 5000.0f;
	//FlightMaxVelocity = 1000.0f;
	FlightMaxVelocity = 2000.0f;
	FlightLinearDamping = 5.0f;
	FlightAngularDamping = 10.0f;

}

// Called when the game starts or when spawned
void AFlyingBot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlyingBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFlyingBot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AFlyingBot::GetFlightAcceleration()
{
	return FlightAcceleration;
}

void AFlyingBot::SetFlightAcceleration(float NewFlightAcceleration)
{
	this->FlightAcceleration = NewFlightAcceleration;
	
}

float AFlyingBot::GetFlightMaxVelocity()
{
	return FlightMaxVelocity;
}

void AFlyingBot::SetFlightMaxVelocity(float NewFlightMaxVelocity)
{
	this->FlightMaxVelocity = NewFlightMaxVelocity;

}

float AFlyingBot::GetFlightLinearDamping()
{
	return FlightLinearDamping;
}

void AFlyingBot::SetFlightLinearDamping(float NewFlightLinearDamping)
{
	this->FlightLinearDamping = NewFlightLinearDamping;

}

float AFlyingBot::GetFlightAngularDamping()
{
	return FlightAngularDamping;
}

void AFlyingBot::SetFlightAngularDamping(float NewFlightAngularDamping)
{
	this->FlightAngularDamping = NewFlightAngularDamping;

}
