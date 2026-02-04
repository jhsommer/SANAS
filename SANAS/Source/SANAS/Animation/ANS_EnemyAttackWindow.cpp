// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_EnemyAttackWindow.h"

#include "SANAS/Characters/Enemies/SANAS_EController.h"
#include "SANAS/Characters/Enemies/SANAS_SimpleEnemy.h"

void UANS_EnemyAttackWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                         float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if(!MeshComp || !MeshComp->GetWorld() || !MeshComp->GetWorld()->IsGameWorld())
	{
		return;
	}
	
	ASANAS_BaseEnemy* Pawn = Cast<ASANAS_BaseEnemy>(MeshComp->GetOwner());
	CashedAIController = Cast<ASANAS_AIController>(Pawn->GetController());

	if(CashedAIController)
	{
		CashedAIController->StartAttackWindow();
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("StartAttackWindow: Pawn=%s"), *GetNameSafe(Pawn));
}

void UANS_EnemyAttackWindow::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (CashedAIController)
	{
		CashedAIController->TickAttackWindow(FrameDeltaTime);
	}
}

void UANS_EnemyAttackWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (CashedAIController)
	{
		CashedAIController->EndAttackWindow();
	}
}
