// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"


class IEnemyInterface;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
/**
 * 
 */
UCLASS()
class GAMESOULSLIKECPP_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	

public:

	AEnemyAIController();

	UFUNCTION(BlueprintCallable)
	void UpDatePatrolLocation();

protected:
	
	virtual void OnPossess(APawn* InPawn) override;
private:	
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
private:

	UPROPERTY()
	APawn* PossessedPawn;

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere)
	UAISenseConfig_Sight* AISightConfig;

	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY()
	TScriptInterface<IEnemyInterface> EnemyInterface;

	UPROPERTY(EditDefaultsOnly)
	FName PatrolLocationKey;

	
	FLinearColor DebugConeColor = FLinearColor::Green;
};
