// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_EnemyAttackWindow.generated.h"

class ASANAS_AIController;
class ASANAS_EController;
/**
 * 
 */
UCLASS()
class SANAS_API UANS_EnemyAttackWindow : public UAnimNotifyState
{
	GENERATED_BODY()
	UPROPERTY()
	TObjectPtr<ASANAS_AIController> CashedAIController = nullptr;
	
	public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
