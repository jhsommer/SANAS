// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/ValueOrBBKey.h"
#include "Animation/AnimationAsset.h"
#include "UBTTask_AttackPlayer.generated.h"

struct FValueOrBBKey_Object;
/**
 * 
 */
UCLASS()
class SANAS_API UUBTTask_AttackPlayer : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(Category= Node, EditAnywhere)
	FValueOrBBKey_Object AnimationToPlay = TObjectPtr<UAnimationAsset>();

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> MyOwnerComp;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> CashedSkelMesh;
	
	
	EAnimationMode::Type PrevAnimMode;

	FTimerDelegate TimerDelegate;
	FTimerHandle TimerHandle;

	void OnAnimationTimerDone();
	void CleanUp(UBehaviorTreeComponent& OwnerComp);

public:
UUBTTask_AttackPlayer(const FObjectInitializer& ObjectInitializer);	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
