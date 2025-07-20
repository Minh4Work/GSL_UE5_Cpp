// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"
#include "Interface/AttackInterface.h"
#include "Componet/HealthComponent.h"

FVector AEnemyCharacter::I_GetEnemyPatrolLocation()
{
	//check if we have patrol points
	if (PatrolPoints.IsEmpty() == true)
	{
		//UE_LOG(LogTemp, Warning, TEXT("No patrol points set for enemy character!, in EnemyCharacter.cpp "));
		return GetActorLocation(); // Return current location if no patrol points are set, Enemy stand still
	}
	//check if PatrolPoints[PatrolIndex] is valid
	if(PatrolPoints[PatrolIndex] == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("PatrolIndex is out of bounds!, in EnemyCharacter.cpp "));
		return GetActorLocation(); // Return current location if PatrolIndex is invalid, Enemy stand still
	}
	// Increment the PatrolIndex to move to the next patrol point
	auto ReturnValue = PatrolPoints[PatrolIndex]->GetActorLocation();

	PatrolIndex = (PatrolIndex + 1) % PatrolPoints.Num();// Loop back to the start of the patrol points

    return ReturnValue;
}

void AEnemyCharacter::I_HandleSeePlayer(AActor* PlayerActor)
{
	AttackInterface_Player = TScriptInterface<IAttackInterface>(PlayerActor);
	if (AttackInterface_Player)
	{
		// Call the I_EnterCombat function on the player's attack interface
		AttackInterface_Player->I_EnterCombat(HealthComponent->Health, HealthComponent->MaxHealth);
	}
}

void AEnemyCharacter::HandleTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DameType, AActor* DamageCauser)
{
	Super::HandleTakePointDamage(DamagedActor, Damage, InstigatedBy, HitLocation, FHitComponent, BoneName, ShotFromDirection, DameType, DamageCauser);

	AttackInterface_Player -> I_HitTarget(HealthComponent->Health,HealthComponent->MaxHealth); 
}

