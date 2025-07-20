// Fill out your copyright notice in the Description page of Project Settings.


#include "Componet/HealthComponent.h"
#include "Data/BaseCharacterDataAsset.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UHealthComponent::SetUpComponent(UBaseCharacterDataAsset* BCD)
{
	// Check if the BaseCharacterData is valid
	if (BCD == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("BaseCharacterData is null in UHealthComponent::SetUpComponent"));
		return;
	}
	Health = BCD->Health;
	MaxHealth = BCD->MaxHealth;
}

void UHealthComponent::UpDateHealthByDame(float Damage)
{
	Health -= Damage;
	Health = FMath::Max(Health, 0.0f);
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
//void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

