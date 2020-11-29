// Copyright 2020 NyeDigital

#pragma once

#include "AIController.h"
#include "Bots/AI/Flying/FlyingBot.h"
#include "World/Zones/SkyTravelLane.h"
#include "Kismet/KismetMathLibrary.h"
#include "../CyberAIController.h"
#include "FlyingAIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

/**
 *
 */
UCLASS()
class CYBERFLIGHT_API AFlyingAIController : public ACyberAIController
{
	GENERATED_BODY()

		AFlyingAIController();

	/* Called whenever the controller possesses a character bot */
	virtual void OnPossess(class APawn* InPawn) override;

	virtual void OnUnPossess() override;

	UFUNCTION(BlueprintCallable, Category = Utility)
		FVector FindAMoveToSkyLaneLocation();

	UFUNCTION(BlueprintCallable, Category = Utility)
	TArray<AActor*> SortedClosestSkyLanesByEntrance(TArray<AActor*> FoundActors);

	int FindSkyLaneIndex(ASkyTravelLane* MySkyTravelLane);

	UBehaviorTreeComponent* BehaviorComp;

	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetActorKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName SelfActorKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName HeliRefKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		FName MoveToLocationKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		FName CurrentSkyLaneKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		FName AllowAccelerationKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		FName MovementStatusKeyName;

public:

	AFlyingBot* FlyingBot;

	AActor* GetTargetActor();

	void SetTargetActor(AActor* NewTargetActor);

	AActor* GetSelfActor();

	void SetSelfActor(AActor* NewSelfActor);

	AActor* GetHeliRef();

	void SetHeliRef(AActor* NewHeliActor);

	FVector GetMoveToLocation();

	void SetMoveToLocation(FVector NewMoveToLocation);

	AActor* GetCurrentSkyLane();

	void SetCurrentSkyLane(AActor* NewCurrentSkyLane);

	bool GetAllowAcceleration();

	void SetAllowAcceleration(bool NewAllowAcceleration);

	FString GetMovementStatus();

	void SetMovementStatus(FString NewMovementStatus);

	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

};
