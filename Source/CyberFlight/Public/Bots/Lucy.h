// Copyright 2020 NyeDigital

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Lucy.generated.h"

UCLASS()
class CYBERFLIGHT_API ALucy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALucy();


	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool Rescue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool Boarding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool Climbing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool Grappling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool Walker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		AActor* TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		bool PlayingMontage;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Utility)
		AActor* GetClosestActorOfClass(TArray<AActor*> FoundActors);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Montage Animation")
		void AnimateIdleInPlace();


};
