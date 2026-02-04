// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_Enemy_DeathFinished.h"

#include "SANAS/Characters/Enemies/SANAS_SimpleEnemy.h"

void UAN_Enemy_DeathFinished::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp|| !MeshComp->GetWorld() || !MeshComp->GetWorld()->IsGameWorld())
		return;
	
	Enemy = Cast<ASANAS_BaseEnemy>(MeshComp->GetOwner());

	//Warum wird das Event nicht getriggert.
	Enemy->EnemyDied();
}
