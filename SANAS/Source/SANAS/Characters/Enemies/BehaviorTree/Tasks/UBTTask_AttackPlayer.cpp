// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTTask_AttackPlayer.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/Tasks/BTTask_PlayAnimation.h"
#include "SANAS/Characters/Enemies/SANAS_BaseEnemy.h"
#include "SANAS/Characters/Enemies/SANAS_EController.h"

void UUBTTask_AttackPlayer::OnAnimationTimerDone()
{ if (MyOwnerComp)
	{
		CleanUp(*MyOwnerComp);
		FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
	}
}

void UUBTTask_AttackPlayer::CleanUp(UBehaviorTreeComponent& OwnerComp)
{
	if (CashedSkelMesh && PrevAnimMode == EAnimationMode::AnimationBlueprint)
	{
		CashedSkelMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	}
}

UUBTTask_AttackPlayer::UUBTTask_AttackPlayer(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	NodeName = "Attack Player";

	bCreateNodeInstance = true;
	TimerDelegate = FTimerDelegate::CreateUObject(this, &UUBTTask_AttackPlayer::OnAnimationTimerDone);
}

EBTNodeResult::Type UUBTTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASANAS_AIController* EnemyController = Cast<ASANAS_AIController>(OwnerComp.GetAIOwner());
	TimerHandle.Invalidate();
	MyOwnerComp = &OwnerComp;
	
	if (!EnemyController || !EnemyController->GetPawn())
	{
		return EBTNodeResult::Failed;
	}

	USkeletalMeshComponent* SkeletalMesh = nullptr;
	ACharacter* MyCharacter = Cast<ACharacter>(EnemyController->GetPawn());

	UAnimationAsset* AnimToPlay = AnimationToPlay.GetValue<UAnimationAsset>(OwnerComp);
	
	if (AnimToPlay)
	{
		AnimToPlay = AnimationToPlay.GetValue<UAnimationAsset>(OwnerComp);

		if (MyCharacter)
		{
			SkeletalMesh = MyCharacter->GetMesh();
		}

		if (SkeletalMesh)
		{
			CashedSkelMesh = SkeletalMesh;
			PrevAnimMode = SkeletalMesh->GetAnimationMode();
			
			SkeletalMesh->PlayAnimation(AnimToPlay, false);
			const float FinishDelay =AnimToPlay->GetPlayLength();

			if (FinishDelay > 0.f)
			{
				EnemyController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, FinishDelay, false);
				return EBTNodeResult::InProgress;
			}

			return EBTNodeResult::Succeeded;
			
		}
		
	}

	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
	
}
