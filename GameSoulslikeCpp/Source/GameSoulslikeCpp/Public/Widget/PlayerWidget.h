// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class GAMESOULSLIKECPP_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpDateHealthBar_Player(float Health, float MaxHealth);

	void UpDateHealthBar_Enemy(float Health, float MaxHealth);

	void ShowEnemyStats();
	void HideEnemyStats();

private:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar_Player;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar_Enemy;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthText_Enemy;
	
};
