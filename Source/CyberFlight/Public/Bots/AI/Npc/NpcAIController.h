// Copyright 2020 NyeDigital

#pragma once

#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Bots/Lucy.h"
#include "Bots/TaxiBotTarget.h"
#include "../CyberAIController.h"
#include "NpcAIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

/**
 * 
 */
UCLASS()
class CYBERFLIGHT_API ANpcAIController : public ACyberAIController
{
	GENERATED_BODY()

	ANpcAIController();

	/* Called whenever the controller possesses a character bot */
	virtual void OnPossess(class APawn* InPawn) override;

	virtual void OnUnPossess() override;

	UBehaviorTreeComponent* BehaviorComp;

	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetActorKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName SelfActorKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName HeliRefKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName StopKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName RescueKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName BoardingKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName ClimbingKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName GrapplingKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName BoardingStatusKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName WalkerKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName WalkerStatusKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName HeliRiderKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName HeliRiderStatusKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName WaitTimeKeyName;

public:

	//AActor* GetTargetActor() const;

	//ASBaseCharacter* GetTargetEnemy() const;

	TArray<AActor*> SortedActorsByDistance(FVector StartingLocation, TArray<AActor*> MyActors);

	ATaxiBotTarget* FindATaxiBotTargetDestination();

	ALucy* LucyBot;

	AActor* GetTargetActor();

	void SetTargetActor(AActor* NewTargetActor);

	AActor* GetSelfActor();

	void SetSelfActor(AActor* NewSelfActor);

	AActor* GetHeliRef();

	void SetHeliRef(AActor* NewHeliActor);

	bool GetStop();

	void SetStop(bool NewStop);

	bool GetRescue();

	void SetRescue(bool NewRescue);

	bool GetBoarding();

	void SetBoarding(bool NewBoarding);

	bool GetClimbing();

	void SetClimbing(bool NewClimbing);

	bool GetGrappling();

	void SetGrappling(bool NewGrappling);

	FString GetBoardingStatus();

	void SetBoardingStatus(FString NewBoardingStatus);

	bool GetWalker();

	void SetWalker(bool NewWalker);

	FString GetWalkerStatus();

	void SetWalkerStatus(FString NewWalkerStatus);

	bool GetHeliRiding();

	void SetHeliRiding(bool NewHeliRiding);

	FString GetHeliRidingStatus();

	void SetHeliRidingStatus(FString NewHeliRidingStatus);

	float GetWaitTime();

	void SetWaitTime(float NewWaitTime);


	//void SetTargetEnemy(APawn* NewTarget);

	//void SetBlackboardBotType(EBotBehaviorType NewType);

	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }



};
