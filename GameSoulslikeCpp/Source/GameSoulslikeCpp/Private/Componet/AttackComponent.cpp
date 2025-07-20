// Fill out your copyright notice in the Description page of Project Settings.


#include "Componet/AttackComponent.h"
#include "GameFramework/Character.h"
#include "Data/BaseCharacterDataAsset.h"
#include "Interface/AttackInterface.h"


// Library kismet
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

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
	const bool bCanAttack = bIsAttacking == false || bCanCombo == true;
	//don't spam attack
	//if (bIsAttacking == true)
	//{
	//	return;
	//}
	//else {
	//// Call the Attack function to perform the attack
	//Attack();
	//}
	if (bCanAttack == true)
	{
		Attack();
	}
	else
	{
		bSavedAttack = true;
	}
}

void UAttackComponent::TraceHit()
{
	// Check if the Character is valid
	if (BaseCharacterDataAsset == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("BaseCharacterDataAsset is null in ABaseCharacter::Tick"));
		return;
	}
	//check Attack Inter Face is valid
	if (AttackInterface== nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("GetMesh is null in ABaseCharacter::Tick"));
		return;
	}

	
	//Hit Results
	TArray<FHitResult> HitResults;
	//line trace 
	//bool bDoHitSomeThing = UKismetSystemLibrary::LineTraceMultiForObjects(
	//	this,
	//	GetActorLocation(),//start location of the trace
	//	GetActorLocation() + GetActorForwardVector() * 1000.0f,//end location of the trace 
	//	//TArray<TEnumAsByte<EObjectTypeQuery>>{ EObjectTypeQuery::ObjectTypeQuery1 }, // Change this to your desired object type
	//	TraceObjecttypes,//object type
	//	false, // bTraceComplex
	//	ActorsToIgnore, // Actors to ignore
	//	EDrawDebugTrace::ForOneFrame, // Draw debug trace
	//	HitResults, // Hit results
	//	true // bIgnoreSelf
	//);
	//Because trace in game a sphere, not line so i change line to sphere
	//Sphere trace
	bool bDoHitSomeThing = UKismetSystemLibrary::SphereTraceMultiForObjects(
		this,
		//GetActorLocation(), // Start location of the trace
		//GetActorLocation() + GetActorForwardVector() * 1000.0f, // End location of the trace
		//trace in weapon
		AttackInterface->I_GetSocketLocation(BaseCharacterDataAsset->WeaponStart), // Start location of the trace, use socket location of the weapon
		AttackInterface->I_GetSocketLocation(BaseCharacterDataAsset->WeaponEnd), // End location of the trace, use socket location of the weapon
		BaseCharacterDataAsset->TraceRadius, // Sphere radius,
		BaseCharacterDataAsset->TraceObjecttypes, // Object types to trace against
		false, // bTraceComplex
		BaseCharacterDataAsset->ActorsToIgnore, // Actors to ignore
		//EDrawDebugTrace::ForDuration, // Draw debug trace for the duration of the game
		BaseCharacterDataAsset->bDebugDrawTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, // Draw debug trace if enabled in the data asset
		HitResults, // Hit results array to fill
		true,// bIgnoreSelf
		FLinearColor::Green, // Color of the debug trace
		FLinearColor::Red, // Color of the trace hit
		BaseCharacterDataAsset->TraceDrawTime // Draw debug trace type
	);
	// Check if the trace hit something
	if (bDoHitSomeThing == false)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Line trace hit something in ABaseCharacter::Tick"));
		return;
	}
	for (const FHitResult& HitResult : HitResults)
	{
		if (HittedActors.Contains(HitResult.GetActor())) continue;
		HandleHitResult(HitResult);
		HittedActors.Emplace(HitResult.GetActor());
	}
	//Print Count Hits
	//FString::Printf(TEXT("Count Hits = %d"),CountHits);
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Red,
			FString::Printf(TEXT("Count Hits = %d"), CountHits)
		);
	}*/
}

void UAttackComponent::HandleHitResult(const FHitResult& HitResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName());
	// Do something with the hit result
	// For example, you can print the name of the hit actor
	//if (HitResult.GetActor())
	//{
	//UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName());
	//}
	//Print the bone name of the hit result
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Red,
			//HitResult.GetActor()->GetName()
			HitResult.BoneName.ToString()// Print the bone name of the hit result
		);
		//Check if the HitSomethingDelegate is bound before executing it
		if (HitSomethingDelegate.IsBound())
		{
			//UE_LOG(LogTemp, Warning, TEXT("HitSomethingDelegate is bound in UAttackComponent::HandleHitResult"));
			HitSomethingDelegate.Execute(HitResult); // Call the delegate with the hit result
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("HitSomethingDelegate is not bound in UAttackComponent::HandleHitResult"));
		}
		
	}
	//UKismetSystemLibrary::DrawDebugSphere(
	//	this,
	//	HitResult.ImpactPoint,
	//	20.0f, // Sphere radius
	//	12, // Segments
	//	FColor::Red, // Color
	//	false, // Persistent
	//	5.0f // Life time
	//);
	//CountHits++;
}

UAnimMontage* UAttackComponent::GetCorrectAttackMontage()
{
	// Check if the BaseCharacterDataAsset is valid
	if (BaseCharacterDataAsset == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("BaseCharacterDataAsset is null in UAttackComponent::GetCorrectAttackMontage"));
		return nullptr;
	}
	// Check AttackAnimationMontages is Empty
	if (BaseCharacterDataAsset->AttackAnimationMontages.IsEmpty())
	{
		//UE_LOG(LogTemp, Warning, TEXT("AttackAnimationMontages is empty in UAttackComponent::GetCorrectAttackMontage"));
		return nullptr;
	}
	return BaseCharacterDataAsset->AttackAnimationMontages[AttackIndex];
	
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
	if (AttackInterface == nullptr || BaseCharacterDataAsset == nullptr || GetCorrectAttackMontage() == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AttackInterface or Attack Animation Montage is null in UAttackComponent::RequestAttack"));
		return;
	}
	else 
	{
		AttackInterface->I_PlayAttackMontage(GetCorrectAttackMontage());
		AttackInterface->I_PlayStartAttackSound();
		bIsAttacking = true;
		bCanCombo = false;
		AttackIndex = (AttackIndex + 1)% BaseCharacterDataAsset->AttackAnimationMontages.Num();	
	}
	//sound start attack
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
	bCanCombo = false;
	bSavedAttack = false;
	AttackIndex = 0;
}

void UAttackComponent::AN_ComboNotify()
{
	//bIsAttacking = true;
	bCanCombo = true;
	if (bSavedAttack == true) {
		RequestAttack();
		bSavedAttack = false;
	}
}

void UAttackComponent::SetUpTraceHit()
{
	//riset hitted actor
	HittedActors.Empty();
	// can't 2 hit in 1 actor, 1 actor only 1 hit
	//reset count hits
	//CountHits = 0;
}

// Called every frame
//void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	
//}

