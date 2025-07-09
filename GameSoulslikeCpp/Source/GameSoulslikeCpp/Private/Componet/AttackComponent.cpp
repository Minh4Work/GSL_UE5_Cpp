// Fill out your copyright notice in the Description page of Project Settings.


#include "Componet/AttackComponent.h"
#include "GameFramework/Character.h"
#include "Data/BaseCharacterDataAsset.h"
#include "Interface/AttackInterface.h"

UAttackComponent::UAttackComponent()
{
	// Sets default values for this component's properties
	PrimaryComponentTick.bCanEverTick = false;

	
}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	// GetOnwer allows me to call the owner of the Component so I cast to character to limit the line of code
	// -- old code --
	//GetOwner() to get the owner of the component, which is the character
	//Character = Cast<ACharacter>(GetOwner());
	// -- new code --
	//Use interface to get the owner
	AttackInterface = TScriptInterface<class IAttackInterface>(GetOwner());
}

void UAttackComponent::RequestAttack()
{
	//don't spam attack
	if (bIsAttacking == true)
	{
		return;
	}
	// Call the Attack function to perform the attack
	Attack();
	
}

void UAttackComponent::Attack()
{
	//Need Character and Animation Montage to play the attack animation
	//check if the Character or AttackAnimationMontage is valid
	//if (Character == nullptr || BaseCharacterDataAsset == nullptr)
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("Character or Attack Animation Montage is null in UAttackComponent::RequestAttack"));
	//	return;
	//}
	//Character->PlayAnimMontage(BaseCharacterDataAsset->AttackAnimationMontage);

	// Use the interface to play the attack montage
	// Check if the AttackInterface and BaseCharacterDataAsset are valid
	if (AttackInterface == nullptr || BaseCharacterDataAsset == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AttackInterface or Attack Animation Montage is null in UAttackComponent::RequestAttack"));
		return;
	}
	AttackInterface->I_PlayAttackMontage(BaseCharacterDataAsset->AttackAnimationMontage);
	bIsAttacking = true;
}

void UAttackComponent::SetUpAttackComponent(UBaseCharacterDataAsset* BCDA)
{
	//First i named BCDA as BasceCharacterDataAsset but it got error, 
	//I guess it can't be same name, so i renamed BCDA to be more concise but still understand that it is BaseCharacterDataAsset
	//Check if the BaseCharacterDataAsset is valid
	//if (BaseCharacterDataAsset == nullptr)
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("BaseCharacterDataAsset is null in UAttackComponent::SetUpAttackComponent"));
	//	return;
	//}
	BaseCharacterDataAsset = BCDA;
	//UE_LOG(LogTemp, Warning, TEXT("BaseCharacterDataAsset is set in UAttackComponent::SetUpAttackComponent"));
}

void UAttackComponent::AN_EndAttackNotify()
{
	bIsAttacking = false;
}




// Called every frame
//void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	
//}

