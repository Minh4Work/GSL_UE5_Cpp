// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "BaseCharacterDataAsset.generated.h"

class UAnimMontage;
/**
 * 
 */
UCLASS()
class GAMESOULSLIKECPP_API UBaseCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	UAnimMontage* AttackAnimationMontage;
	
	//---Hit React Animations---
	UPROPERTY(EditDefaultsOnly, Category = "Hit React")
	UAnimMontage* HitReactAnimationMontageBack;

	UPROPERTY(EditDefaultsOnly, Category = "Hit React")
	UAnimMontage* HitReactAnimationMontageFront;

	UPROPERTY(EditDefaultsOnly, Category = "Hit React")
	UAnimMontage* HitReactAnimationMontageLeft;
	
	UPROPERTY(EditDefaultsOnly, Category = "Hit React")
	UAnimMontage* HitReactAnimationMontageRight;

	//Trace hit
	//object types for trace
	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjecttypes;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceRadius = 10.0f; // Radius for the trace

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceDrawTime = 2.0f;

	//socket name for the weapon
	UPROPERTY(EditDefaultsOnly, Category = "WeaponTrace")
	FName WeaponStart;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponTrace")
	FName WeaponEnd;

	//Stats
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float AttackDamage = 10.0f; // Damage dealt by the attack

	//Debug
	UPROPERTY(EditDefaultsOnly, Category = "Debug")
	bool bDebugDrawTrace = true; // Whether to draw debug traces
};
