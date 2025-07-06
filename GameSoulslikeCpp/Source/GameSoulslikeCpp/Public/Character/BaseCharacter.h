// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UEnhenceInPutDataAsset;
struct FInputActionValue;


UCLASS()
class GAMESOULSLIKECPP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ABaseCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	
	virtual void BeginPlay() override;
	void AddMappingContextForCharacter();
private:
	void Look(const FInputActionValue& Value);
	void Movement(const FInputActionValue& Value);
private:	
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "CharacterData")
	UEnhenceInPutDataAsset* EnhenceInPutData;
};
