// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"


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

private:
	UPROPERTY()
	ACharacter* Character;

	UPROPERTY()
	UCharacterMovementComponent* CharacterMovement;

	float GroundSpeed = 0.0f;
};
