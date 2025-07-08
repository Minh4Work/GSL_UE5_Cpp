// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Data/EnhenceInPutDataAsset.h"
#include "Componet/AttackComponent.h"

// library Enhanced Input
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ABaseCharacter::ABaseCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	//--- Camera ---
	//create a spring arm component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	// Disable rotation of the arm with the pawn's control rotation
	SpringArmComponent->bUsePawnControlRotation = true;
	// Set the length of the arm
	SpringArmComponent->TargetArmLength = 400.0f;
	// Set the arm to be slightly above the character
	SpringArmComponent->AddLocalOffset(FVector(0.0f, 0.0f, 50.0f));
	//create a camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	// Disable camera rotation with the pawn's control rotation
	CameraComponent->bUsePawnControlRotation = false;

	// Set the character to not rotate with the controller's yaw
	bUseControllerRotationYaw = false;
	
	//--- Movement ---
	// Character will rotate to the direction of movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//set the rotation rate Yaw of the character
	//GetCharacterMovement()->RotationRate.Y = 540.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	//--- Attack Component ---
	// Create the attack component
	AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackComponent"));

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	AddMappingContextForCharacter();
	//Enhanced Input component
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// Check if the EnhenceInPutData is valid	
	if (EnhenceInPutData == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("EnhenceInPutData is null in ABaseCharacter::BeginPlay"));
		return;
	}

	//Look
	EnhancedInputComponent->BindAction(EnhenceInPutData->IA_Look, ETriggerEvent:: Triggered, this, &ABaseCharacter::Look);
	//Movement
	EnhancedInputComponent->BindAction(EnhenceInPutData->IA_Movement, ETriggerEvent::Triggered, this, &ABaseCharacter::Movement);
	//Attack
	EnhancedInputComponent->BindAction(EnhenceInPutData->IA_Attack, ETriggerEvent::Started, this, &ABaseCharacter::AttackPressed);
}

void ABaseCharacter::PostInitializeComponents()
{
	//call before all components are initialized
	Super::PostInitializeComponents();
	//call AttackComponent Setup function
	// Check if the AttackComponent is valid
	if (AttackComponent == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AttackComponent is null in ABaseCharacter::PostInitializeComponents"));
		return;
	}
	AttackComponent->SetUpAttackComponent(BaseCharacterDataAsset);

}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::AddMappingContextForCharacter()
{
	// Add mapping context to the player controller
	// Need local player to add mapping context
	// Get the player controller and local player
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	// Check if the player controller is valid
	if (PlayerController == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("PlayerController is null in ABaseCharacter::BeginPlay"));
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	// Check if the subsystem is valid
	if (Subsystem == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Subsystem is null in ABaseCharacter::BeginPlay"));
		return;
	}

	//add the input mapping context
	// Check if the EnhenceInPutData is valid	
	if (EnhenceInPutData == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("EnhenceInPutData is null in ABaseCharacter::BeginPlay"));
		return;
	}

	Subsystem->AddMappingContext(EnhenceInPutData->InputMappingContext, 0);
}



void ABaseCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();

	// Check if the look.X value is zero
	if(LookValue.X == 0.0f)
	{
		return;
	}

	// Add controller yaw input based on the look value
	AddControllerYawInput(LookValue.X);
	// Check if the look value.Y is zero for Y axis
	if(LookValue.Y == 0.0f)
	{
		return;
	}

	AddControllerPitchInput(LookValue.Y);
}

void ABaseCharacter::Movement(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();
	// Check if the movement value is zero
	if(MovementValue.IsZero())
	{
		return;
	}
	
	const FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	//Forward and backward movement based on the control rotation
	//Forward vector based on the control rotation = Vector (1, 0, 0)
	const FVector ForwardVecter = ControlRotation.RotateVector(FVector::ForwardVector);
	// check if the forward vector is zero
	if(MovementValue.Y != 0)
	{
		AddMovementInput(ForwardVecter, MovementValue.Y);
	}
	
	//Right and left movement based on the control rotation
	//Right vector based on the control rotation = Vector (0, 1, 0)
	const FVector RightVector = ControlRotation.RotateVector(FVector::RightVector);
	// check if the right vector is zero
	if (MovementValue.X != 0)
	{
		AddMovementInput(RightVector, MovementValue.X);
	}

	/*why not check like obove ?
	*Because if return early then can not move left right
	*/
}

void ABaseCharacter::AttackPressed()
{
	//PlayAnimMontage(EnhenceInPutData->IA_Attack->GetAnimMontage());
	//PlayAnimMontage(AttackAnimationMontage);
	//Check if the attack component is valid
	if (AttackComponent == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AttackComponent is null in ABaseCharacter::AttackPressed"));
		return;
	}
	AttackComponent->RequestAttack();
}
