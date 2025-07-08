// Fill out your copyright notice in the Description page of Project Settings.


#include "Componet/AttackComponent.h"
#include "GameFramework/Character.h"
#include "Data/BaseCharacterDataAsset.h"

UAttackComponent::UAttackComponent()
{
	// Sets default values for this component's properties
	PrimaryComponentTick.bCanEverTick = false;

	
}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	// GetOnwer allows me to call the owner of the Component so I cast to character to limit the line of code
	Character = Cast<ACharacter>(GetOwner());
}

void UAttackComponent::RequestAttack()
{
	//Need Character and Animation Montage to play the attack animation
	//check if the Character or AttackAnimationMontage is valid
	if (Character == nullptr || BaseCharacterDataAsset == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Character or Attack Animation Montage is null in UAttackComponent::RequestAttack"));
		return;
	}
	Character->PlayAnimMontage(BaseCharacterDataAsset->AttackAnimationMontage);
}

void UAttackComponent::SetUpAttackComponent(UBaseCharacterDataAsset* BCDA)
{
	//First i named BCDA as BasceCharacterDataAsset but it got error, 
	//I guess it can't be same name, so i renamed BCDA to be more concise but still understand that it is BaseCharacterDataAsset
	// Check if the BaseCharacterDataAsset is valid
	//if (BaseCharacterDataAsset == nullptr)
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("BaseCharacterDataAsset is null in UAttackComponent::SetUpAttackComponent"));
	//	return;
	//}
	BaseCharacterDataAsset = BCDA;
	//UE_LOG(LogTemp, Warning, TEXT("BaseCharacterDataAsset is set in UAttackComponent::SetUpAttackComponent"));
}




// Called every frame
//void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	
//}

