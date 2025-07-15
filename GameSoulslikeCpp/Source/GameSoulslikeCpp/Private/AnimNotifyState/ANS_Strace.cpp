// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState/ANS_Strace.h"
#include "Interface/AttackInterface.h"

void UANS_Strace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	// MeshComp is the skeletal mesh component of the character
	//check if the MeshComp is valid
	if (MeshComp == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("MeshComp is null in UANS_Strace::NotifyBegin"));
		return;
	}
	AttackInterface = TScriptInterface<IAttackInterface>(MeshComp->GetOwner());
	//check if the AttackInterface is valid
	if (!AttackInterface)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AttackInterface is null in UANS_Strace::NotifyBegin"));
		return;
	}
	AttackInterface->I_ANS_BeginTraceHitNotify();
}

void UANS_Strace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	// Check if the AttackInterface is valid
	if (!AttackInterface)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AttackInterface is null in UANS_Strace::NotifyTick"));
		return;
	}
	AttackInterface->I_ANS_TraceHitNotify();

}
