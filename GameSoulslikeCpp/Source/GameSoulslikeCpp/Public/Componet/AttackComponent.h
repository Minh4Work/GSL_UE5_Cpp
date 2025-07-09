// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "AttackComponent.generated.h"

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
	
	void SetUpAttackComponent(UBaseCharacterDataAsset* BCDA);
	void AN_EndAttackNotify();

private:

	void Attack();
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
};
