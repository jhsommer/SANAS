// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_Enemy_DeathFinished.generated.h"

class ASANAS_BaseEnemy;
class ASANAS_SimpleEnemy;
/**
 * 
 */
UCLASS()
class SANAS_API UAN_Enemy_DeathFinished : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY()
	TObjectPtr<ASANAS_BaseEnemy> Enemy;
};
