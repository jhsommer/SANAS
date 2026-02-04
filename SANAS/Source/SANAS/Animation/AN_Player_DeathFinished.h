// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_Player_DeathFinished.generated.h"

class ASANAS_Player;
/**
 * 
 */
UCLASS()
class SANAS_API UAN_Player_DeathFinished : public UAnimNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY()
	TObjectPtr<ASANAS_Player> Player =  nullptr;
};
