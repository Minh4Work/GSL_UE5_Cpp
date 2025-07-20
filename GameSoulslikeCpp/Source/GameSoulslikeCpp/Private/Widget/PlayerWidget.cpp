// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerWidget::UpDateHealthBar_Player(float Health, float MaxHealth)
{	
	//check if the NewPercent is valid
	if (HealthBar_Player == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("HealthBar_Player is null in UPlayerWidget::UpDateHealthBar_Player"));
		return;
	}
	float NewPercent = Health / MaxHealth;
	HealthBar_Player->SetPercent(NewPercent);
	//if (HealthText)
	//{
	//	//HealthText->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), NewPercent * 100.0f)));
	//}
}

void UPlayerWidget::UpDateHealthBar_Enemy(float Health, float MaxHealth)
{
	//check if the NewPercent is valid
	if (HealthBar_Enemy == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("HealthBar_Enemy is null in UPlayerWidget::UpDateHealthBar_Enemy"));
		return;
	}
	float NewPercent = Health / MaxHealth;
	HealthBar_Enemy->SetPercent(NewPercent);

	FString HealthString = FString::Printf(TEXT("%d / %d"),FMath::CeilToInt(Health), FMath::CeilToInt(MaxHealth));

	//check if HealthText_Enemy is valid
	if (HealthText_Enemy == nullptr) 
	{
		//UE_LOG(LogTemp, Warning, TEXT("HealthText_Enemy is null in UPlayerWidget::UpDateHealthBar_Enemy"));
		return;
	}
	HealthText_Enemy->SetText(FText::FromString(HealthString));
}

void UPlayerWidget::ShowEnemyStats()
{
	//check if the HealthBar_Enemy and HealthText_Enemy are valid
	if (HealthBar_Enemy == nullptr || HealthText_Enemy == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("HealthBar_Enemy or HealthText_Enemy is null in UPlayerWidget::ShowEnemyStats"));
		return;
	}
	HealthBar_Enemy->SetVisibility(ESlateVisibility::Visible);
	HealthText_Enemy->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerWidget::HideEnemyStats()
{
	//check if the HealthBar_Enemy and HealthText_Enemy are valid
	if (HealthBar_Enemy == nullptr || HealthText_Enemy == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("HealthBar_Enemy or HealthText_Enemy is null in UPlayerWidget::ShowEnemyStats"));
		return;
	}
	HealthBar_Enemy->SetVisibility(ESlateVisibility::Hidden);
	HealthText_Enemy->SetVisibility(ESlateVisibility::Hidden);
}
