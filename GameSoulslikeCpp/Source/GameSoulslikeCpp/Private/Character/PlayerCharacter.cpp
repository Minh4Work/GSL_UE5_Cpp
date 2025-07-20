// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "Widget/PlayerWidget.h"
#include "Componet/HealthComponent.h"

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass);

	// Check if the PlayerWidget is valid
	if (PlayerWidget == nullptr || HealthComponent == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("PlayerWidget or HealthComponent could not be created!"));
		return;
	}
	else
	{
		PlayerWidget->AddToViewport();
		PlayerWidget->UpDateHealthBar_Player(HealthComponent-> Health , HealthComponent->MaxHealth); // Initialize health bar to full
		PlayerWidget->HideEnemyStats(); // Hide enemy stats at the start
	}
}

void APlayerCharacter::I_EnterCombat(float Health_Enemy, float MaxHealth_Enemy)
{
	// Update the enemy health bar in the player widget
	if (PlayerWidget == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("PlayerWidget is null in APlayerCharacter::I_EnterCombat"));
		return;
	}
	PlayerWidget->ShowEnemyStats(); // Show enemy stats when entering combat
	PlayerWidget->UpDateHealthBar_Enemy(Health_Enemy, MaxHealth_Enemy);
}

void APlayerCharacter::I_HitTarget(float Health_target, float MaxHealth_Target)
{
	// Update the enemy health bar in the player widget
	if (PlayerWidget == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("PlayerWidget is null in APlayerCharacter::I_EnterCombat"));
		return;
	}
	PlayerWidget->UpDateHealthBar_Enemy(Health_target, MaxHealth_Target);
}
