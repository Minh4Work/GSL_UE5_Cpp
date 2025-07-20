// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/AttackInterface.h"
#include "Enum/CombatState.h"

#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UEnhenceInPutDataAsset;
class UAttackComponent;
class UHealthComponent;
class UBaseCharacterDataAsset;
struct FInputActionValue;


UCLASS()
class GAMESOULSLIKECPP_API ABaseCharacter : public ACharacter, public IAttackInterface
{
	GENERATED_BODY()

public:
	
	ABaseCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	//virtual void Tick(float DeltaSeconds) override;

	//Attack Interface
	virtual void I_PlayAttackMontage(UAnimMontage* AttackMontage) override;
	virtual void I_PlayStartAttackSound() override;
	virtual void I_AN_EndAttackNotify() override;
	virtual void I_AN_ComboNotify() override;
	virtual void I_ANS_TraceHitNotify() override;
	virtual void I_ANS_BeginTraceHitNotify() override;

	virtual FVector I_GetSocketLocation(const FName& SocketName) const override;
	
protected:
	
	virtual void BeginPlay() override;
	void AddMappingContextForCharacter();
	
	UFUNCTION()
	virtual void HandleTakePointDamage(AActor* DamagedActor, float Damage, 
		class AController* InstigatedBy,FVector HitLocation,
		class UPrimitiveComponent* FHitComponent, FName BoneName, 
		FVector ShotFromDirection, const class UDamageType* DameType, AActor* DamageCauser);
private:

	UAnimMontage* GetCorrectHitReactMontage(const FVector& AttackDirection) const;
	void Look(const FInputActionValue& Value);
	void Movement(const FInputActionValue& Value);
	void AttackPressed();

	//event function when hit something
	UFUNCTION()
	void HandleHitSomething(const FHitResult& HitResult);

protected:

	UPROPERTY(VisibleAnywhere)
	UAttackComponent* AttackComponent;

	UPROPERTY(VisibleAnywhere)
	UHealthComponent* HealthComponent;

private:	
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "CharacterData")
	UEnhenceInPutDataAsset* EnhenceInPutData;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterData")
	UBaseCharacterDataAsset* BaseCharacterDataAsset;
	
	
	EStatsCombat StatsCombat = EStatsCombat::Ready;
//Get & set
public:

	FORCEINLINE
	EStatsCombat GetStatsCombat() const { return StatsCombat; }
};

