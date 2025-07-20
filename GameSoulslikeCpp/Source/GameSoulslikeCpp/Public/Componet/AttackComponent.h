// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "AttackComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FHitSomethingDelegate, const FHitResult&, HitResult);

class UBaseCharacterDataAsset;
class IAttackInterface;
class ACharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMESOULSLIKECPP_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UAttackComponent();
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void RequestAttack();
	void TraceHit();

	
	
	void SetUpAttackComponent(UBaseCharacterDataAsset* BCDA);
	void AN_EndAttackNotify();
	void AN_ComboNotify();
	void SetUpTraceHit();

private:

	void Attack();
	void HandleHitResult(const FHitResult& HitResult);
	UAnimMontage* GetCorrectAttackMontage();

public:
	FHitSomethingDelegate HitSomethingDelegate;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	//pawn address pointer has interface
	UPROPERTY()
	TScriptInterface<class IAttackInterface> AttackInterface;

	UPROPERTY()
	UBaseCharacterDataAsset* BaseCharacterDataAsset;

	UPROPERTY();
	ACharacter* Character;

	bool bIsAttacking = false;
	bool bCanCombo = false;
	bool bSavedAttack = false; 

	int AttackIndex = 0;
	
	TArray<AActor*> HittedActors;
	// Count hits
	//int CountHits = 0;
};
