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
};
