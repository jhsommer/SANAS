// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_Player_DeathFinished.h"

#include "SANAS/Characters/Player/SANAS_Player.h"


void UAN_Player_DeathFinished::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                      const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp|| !MeshComp->GetWorld() || !MeshComp->GetWorld()->IsGameWorld())
		return;
	
	Player = Cast<ASANAS_Player>(MeshComp->GetOwner());

	Player->PlayerDied();
}
