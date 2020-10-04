// Copyright 2020 NyeDigital

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CannonTarget.generated.h"

UCLASS()
class CYBERFLIGHT_API ACannonTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannonTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	/** Sphere collision component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		class USphereComponent* CollisionComp;

};
