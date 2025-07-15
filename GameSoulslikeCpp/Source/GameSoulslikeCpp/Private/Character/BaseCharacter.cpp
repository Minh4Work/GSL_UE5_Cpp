// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Data/EnhenceInPutDataAsset.h"
#include "Componet/AttackComponent.h"
#include "Data/BaseCharacterDataAsset.h"

//Library kismet
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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
	AttackComponent->HitSomethingDelegate.BindDynamic(this, &ABaseCharacter::HandleHitSomething);
	AttackComponent->SetUpAttackComponent(BaseCharacterDataAsset);

}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnTakePointDamage.AddDynamic(this,&ABaseCharacter::HandleTakePointDamage );
}

//void ABaseCharacter::Tick(float DeltaSeconds)
//{
//	Super::Tick(DeltaSeconds);
//}

#pragma region Attack Interface Functions
void ABaseCharacter::I_PlayAttackMontage(UAnimMontage* AttackMontage)
{
	// Play the attack montage for the character
	// Check if the AttackMontage is valid
	if (AttackMontage == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AttackMontage is null in ABaseCharacter::I_PlayAttackMontage"));
		return;
	}
	PlayAnimMontage(AttackMontage);
}

void ABaseCharacter::I_AN_EndAttackNotify()
{
	// This function is called when the attack animation ends
	// It can be used to reset the attack state or trigger other actions
	//UE_LOG(LogTemp, Warning, TEXT("Attack animation ended in ABaseCharacter::I_AN_EndAttackNotify"));
	//IsAttacking is false so that the character can attack again
	// Check if the AttackComponent is valid
	if (AttackComponent == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AttackComponent is null in ABaseCharacter::I_AN_EndAttackNotify"));
		return;
	}
	AttackComponent->AN_EndAttackNotify();
	
}

void ABaseCharacter::I_AN_ComboNotify()
{
	// This function is called when the combo animation is triggered
	// It can be used to reset the combo state or trigger other actions
	//UE_LOG(LogTemp, Warning, TEXT("Combo animation triggered in ABaseCharacter::I_AN_ComboNotify"));
	// Check if the AttackComponent is valid
	if (AttackComponent == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AttackComponent is null in ABaseCharacter::I_AN_ComboNotify"));
		return;
	}
	AttackComponent->AN_ComboNotify();
}

void ABaseCharacter::I_ANS_BeginTraceHitNotify()
{
	// This function is called when the trace hit animation begins
	// It can be used to reset the trace hit state or trigger other actions
	//UE_LOG(LogTemp, Warning, TEXT("Trace hit animation began in ABaseCharacter::I_ANS_BeginTraceHitNotify"));
	// Check if the AttackComponent is valid
	if (AttackComponent == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AttackComponent is null in ABaseCharacter::I_ANS_BeginTraceHitNotify"));
		return;
	}
	AttackComponent->SetUpTraceHit();
}

void ABaseCharacter::I_ANS_TraceHitNotify()
{
	// Check if the AttackComponent is valid
	if (AttackComponent == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AttackComponent is null in ABaseCharacter::Tick"));
		return;
	}
	AttackComponent->TraceHit();
}

FVector ABaseCharacter::I_GetSocketLocation(const FName& SocketName) const
{
	// Check if the GetMesh is valid
	if (GetMesh() == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("GetMesh is null in ABaseCharacter::I_GetSocketLocation"));
		return FVector();
	}
	return GetMesh()-> GetSocketLocation(SocketName);
	//return FVector();
}
#pragma endregion
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

void ABaseCharacter::HandleHitSomething(const FHitResult& HitResult)
{
	// Check if the Base Character is valid
	if (BaseCharacterDataAsset == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("BaseCharacterDataAsset is null in ABaseCharacter::HandleHitSomething"));
		return;
	}
	//notify the attack component that hit something
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			1.f,
			FColor::Red,
			////HitResult.GetActor()->GetName()
			//HitResult.BoneName.ToString()// Print the bone name of the hit result
			TEXT("Hit Something")
		);
	}

	// Check if the hit actor is valid
	if (HitResult.GetActor() == nullptr)
	{
		return;
	}
	 const auto AttackDirection = UKismetMathLibrary::GetDirectionUnitVector(
		GetActorLocation(),
		HitResult.GetActor()->GetActorLocation()
	);
	UGameplayStatics::ApplyPointDamage(
		HitResult.GetActor(),// Actor hit
		BaseCharacterDataAsset->AttackDamage,//dame
		AttackDirection,// Direction of the attack
		HitResult,//
		GetController(),// controller
		this,//Weapon but already mounted on the character
		//BaseCharacterDataAsset->DamageType
		UDamageType::StaticClass()// Damage type
	);
}

void ABaseCharacter::HandleTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DameType, AActor* DamageCauser)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Red,
			//FString::Printf(TEXT("Damaged Actor: %s, Damage: %f, Bone Name: %s"), *DamagedActor->GetName(), Damage, *BoneName.ToString())
			TEXT("Handle Take Point Damage")
		);
		//check if the BaseCharacterDataAsset is valid
		if (BaseCharacterDataAsset == nullptr)
		{
			//UE_LOG(LogTemp, Warning, TEXT("BaseCharacterDataAsset is null in ABaseCharacter::HandleTakePointDamage"));
			return;
		}
		else {
			
			PlayAnimMontage(GetCorrectHitReactMontage(ShotFromDirection));
			StatsCombat = EStatsCombat::Beaten;
		}
	}
}

UAnimMontage* ABaseCharacter::GetCorrectHitReactMontage(const FVector& AttackDirection) const
{
	//check if the BaseCharacterDataAsset is valid
	if (BaseCharacterDataAsset == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("BaseCharacterDataAsset is null in ABaseCharacter::GetCorrectHitReactMontage"));
		return nullptr;
	}

	//Apply Dot product to determine the direction of the attack - Back , Front
	auto Dot = FVector::DotProduct(AttackDirection, GetActorForwardVector());
	//test Dot
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Red,
			FString::Printf(TEXT("Dot: %f"), Dot)
		);
	}
	//Apply Cross product to determine the direction of the attack - Left , Right
	FVector Cross = FVector::CrossProduct(AttackDirection, GetActorForwardVector());
	//test Cross
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Red,
			FString::Printf(TEXT("Cross: %f %f %f"), Cross.X, Cross.Y, Cross.Z)
		);
	}

	//If Abs(Dot) < 0.5f use Cross
	//If Dot > 1 Back
	//If Dot < -1 Front
	//If Cross.Z < 0 Left
	//If Cross.Z > 0 Right 
	//return UAnimMontage();

	if (FMath::Abs(Dot) < 0.5f)
	{
		if (Cross.Z < 0)
		{
			return BaseCharacterDataAsset->HitReactAnimationMontageLeft;
		}
		else
		{
			return BaseCharacterDataAsset->HitReactAnimationMontageRight;
		}
	}
	else if (Dot > 0.5f)
	{
		return BaseCharacterDataAsset->HitReactAnimationMontageBack;
	}
	else if (Dot < -0.5f)
	{
		return BaseCharacterDataAsset->HitReactAnimationMontageFront;
	}
	return nullptr;
}
