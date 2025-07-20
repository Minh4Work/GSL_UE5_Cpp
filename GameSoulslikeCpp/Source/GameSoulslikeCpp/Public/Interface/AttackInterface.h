// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "AttackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMESOULSLIKECPP_API IAttackInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	 * Play the attack montage for the character.
	 * @param AttackMontage - The animation montage to play for the attack.
	 * function = 0 because classes that call this Interface will redefine this Interface
	 */
	virtual void I_PlayAttackMontage(UAnimMontage* AttackMontage) = 0;
	virtual void I_PlayStartAttackSound() = 0;
	virtual void I_AN_EndAttackNotify() = 0;
	virtual void I_AN_ComboNotify() = 0;
	virtual FVector I_GetSocketLocation(const FName& SocketName) const = 0;
	virtual void I_ANS_TraceHitNotify() = 0;
	virtual void I_ANS_BeginTraceHitNotify() = 0;


	virtual void I_EnterCombat(float Health_Enemy, float MaxHealth_Enemy);
	virtual void I_HitTarget(float Health_target, float MaxHealth_Target);
};
