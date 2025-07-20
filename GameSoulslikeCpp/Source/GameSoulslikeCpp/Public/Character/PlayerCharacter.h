// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UPlayerWidget;
/**
 * 
 */
UCLASS()
class GAMESOULSLIKECPP_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:	

	virtual void I_EnterCombat(float Health_Enemy, float MaxHealth_Enemy) override;
	virtual void I_HitTarget(float Health_target, float MaxHealth_Target) override; 
protected:
	void BeginPlay() override;
private:

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> PlayerWidgetClass;

	UPROPERTY()
	UPlayerWidget* PlayerWidget;
};
