// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

class ABaseCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class GAMESOULSLIKECPP_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeInitializeAnimation() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected: 

	UPROPERTY(BlueprintReadOnly)
	bool bCanMove = false;

	UPROPERTY(BlueprintReadOnly)
	bool bCanBlendLowerUpper = true;

private:
	UPROPERTY()
	ABaseCharacter* BaseCharacter;

	UPROPERTY()
	UCharacterMovementComponent* CharacterMovement;

	float GroundSpeed = 0.0f;
};
