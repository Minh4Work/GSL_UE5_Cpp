// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/EnemyAIController.h"
#include "Interface/EnemyInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
//#include "EnemyAIController.h"
// --kismet--
#include <Kismet/KismetSystemLibrary.h>
//---set up Enemy  ---

AEnemyAIController::AEnemyAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	//set up sight config
	AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISightConfig"));

	AISightConfig->SightRadius = 1500.0f; // Set the sight radius
	AISightConfig->LoseSightRadius = AISightConfig->SightRadius + 0.0f; // Set the lose sight radius
	//55.0f = 110 degrees, 45.0f = 90 degrees, 60.0f = 120 degrees, 90.0f = 180 degrees, 120.0f = 240 degrees
	AISightConfig->PeripheralVisionAngleDegrees = 55.0f; // Set the peripheral vision angle
	//Set faction, there are enemies, friends, neutral, i think neutral will be good for starting
	AISightConfig->DetectionByAffiliation.bDetectNeutrals = true; // Set the detection by affiliation
	
	//indicates that AIPerceptionComponent uses the AISightConfig
	AIPerceptionComponent->ConfigureSense(*AISightConfig); // Configure the AIPerceptionComponent with the AISightConfig
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	EnemyInterface = TScriptInterface<IEnemyInterface>(InPawn);

	//RunBehaviorTree(BehaviorTreeAsset);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::HandleTargetPerceptionUpdated);
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Update the patrol location in the blackboard
	PossessedPawn = GetPawn();
	//check if the pawn is valid
	if(PossessedPawn == nullptr)
	{
		return;
	}
	//draw debug cone for the AI sight
	UKismetSystemLibrary::DrawDebugCone(
		this,
		PossessedPawn->GetActorLocation(),// Get the location of the pawn
		PossessedPawn->GetActorForwardVector(),// Get the forward vector of the pawn
		AISightConfig->SightRadius,// Use the sight radius from the AISightConfig
		FMath::DegreesToRadians(AISightConfig->PeripheralVisionAngleDegrees),// Use the peripheral vision angle from the AISightConfig
		FMath::DegreesToRadians(AISightConfig->PeripheralVisionAngleDegrees),// Use the peripheral vision angle from the AISightConfig
		20.0f,// The number of segments in the cone
		DebugConeColor,// The color of the cone
		-0.1f,
		3.0f
	);
}

void AEnemyAIController::HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(Stimulus.WasSuccessfullySensed())
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,
				5.f,
				FColor::Green,
				TEXT("EnemyAIController: Successfully sensed an actor!"));
		}
		DebugConeColor = FLinearColor::Red;

		// Check the EnemyInterface is valid
		if(EnemyInterface.GetInterface() == nullptr)
		{
			return;
		}
		EnemyInterface->I_HandleSeePlayer(Actor);
	}
	else
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,
				5.f,
				FColor::Red,
				TEXT("EnemyAIController: Failed to sense an actor!"));
		}
		DebugConeColor = FLinearColor::Green;
	}
}

void AEnemyAIController::UpDatePatrolLocation()
{
	
	//EnemyInterface->I_GetEnemyPatrolLocation(); 
	//check if the interface is valid and blackboard is valid
	if(!EnemyInterface.GetInterface() || !Blackboard)
	{
		//UE_LOG(LogTemp, Warning, TEXT("EnemyInterface or Blackboard is not valid in EnemyAIController::UpDatePatrolLocation"));
		return;
	}
	//Set up the patrol location in the blackboard
	Blackboard->SetValueAsVector("PatrolLocation", EnemyInterface->I_GetEnemyPatrolLocation());
}