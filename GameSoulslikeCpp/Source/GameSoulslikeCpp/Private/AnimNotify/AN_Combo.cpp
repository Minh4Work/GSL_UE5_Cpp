// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AN_Combo.h"
#include "Interface/AttackInterface.h"

void UAN_Combo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	//MeshComp is the skeletal mesh component of the character
	//check if the MeshComp is valid
	if (MeshComp == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("MeshComp is null in UAN_EndAttack::Notify"));
		return;
	}
	auto AttackInterface = TScriptInterface<class IAttackInterface>(MeshComp->GetOwner());

	//check if the AttackInterface is valid
	if (AttackInterface == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AttackInterface is null in UAN_EndAttack::Notify"));
		return;
	}
	AttackInterface->I_AN_ComboNotify();
}
