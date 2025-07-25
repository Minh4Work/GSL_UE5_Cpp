// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UBaseCharacterDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMESOULSLIKECPP_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetUpComponent(UBaseCharacterDataAsset* BCD);
	void UpDateHealthByDame(float Damage);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	float Health = 0.0f; // Default health value
	float MaxHealth = 0.0f; // Maximum health value
	

		
};
