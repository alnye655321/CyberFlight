// Copyright 2020 NyeDigital

#pragma once

#include "GameFramework/Actor.h"
#include "Zone.generated.h"

UCLASS()
class CYBERFLIGHT_API AZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// root component for everything else to be attached to
	// A SceneComponent has a transform and supports attachment, but has no rendering or collision capabilities. Useful as a 'dummy' component in the hierarchy to offset others
	UPROPERTY(EditAnywhere)
		USceneComponent* ZoneRoot;

	// collision box
	UPROPERTY(EditAnywhere)
		UShapeComponent* CollisionBox;

};
