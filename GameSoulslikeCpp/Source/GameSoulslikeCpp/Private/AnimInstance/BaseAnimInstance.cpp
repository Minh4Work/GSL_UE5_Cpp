// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/BaseAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	//Character Movement Component
	//Pawn cast to ACharacter
	Character = Cast<ACharacter> (TryGetPawnOwner());
	//Check if the character is valid
	if (Character == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Character is null in UBaseAnimInstance::NativeInitializeAnimation"));
		return;
	}
	CharacterMovement = Character->GetCharacterMovement();
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{	
	
	//Need movement component to get the velocity
	//check if the character movement component is valid
	if(CharacterMovement == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("CharacterMovement is null in UBaseAnimInstance::NativeUpdateAnimation"));
		return;
	}
	//CharacterMovement->Velocity;
	//Speed
	GroundSpeed = UKismetMathLibrary::VSizeXY (CharacterMovement->Velocity);
	
	//Can Move
	bCanMove = GroundSpeed > 0.0f;
}
