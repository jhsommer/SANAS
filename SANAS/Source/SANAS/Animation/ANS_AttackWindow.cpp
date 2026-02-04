// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_AttackWindow.h"

#include "SANAS/Characters/Player/SANAS_Player.h"

void UANS_AttackWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                    const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if(!MeshComp || !MeshComp->GetWorld() || !MeshComp->GetWorld()->IsGameWorld())
	{
		return;
	}
	
	Player = Cast<ASANAS_Player>(MeshComp->GetOwner());

	Player->StartAttackWindow();
}

void UANS_AttackWindow::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
	if (Player)
	{
		Player->TickAttackWindow(FrameDeltaTime);
	}
}

void UANS_AttackWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (Player)
	{
		Player->EndAttackWindow();
	}
}
