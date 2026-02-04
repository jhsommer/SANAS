// Fill out your copyright notice in the Description page of Project Settings.


#include "SANAS_EController.h"

#include "SANAS_SimpleEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SANAS/Utils/SockeUtils.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "SANAS/Characters/Player/SANAS_Player.h"


// Sets default values
ASANAS_EController::ASANAS_EController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void ASANAS_EController::StartAttackWindow()
{
	CashedEnemy= Cast<ASANAS_SimpleEnemy>(GetPawn());
	if (!CashedEnemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn Cast Failed in AIController in Simple Enemy"))
		UE_LOG(LogTemp, Warning, TEXT("Pawn class: %s"),*GetPawn()->GetClass()->GetName());
		return;
	}
	
	CapsuleOrigin = SocketUtils::GetSocketTransform(CashedEnemy->GetSword(), SwordOriginSocket.GetTagName());
	CapsuleRadius = SocketUtils::GetDistanceBetweenSockets(CashedEnemy->GetSword(), SwordOriginSocket.GetTagName(), SwordRadiusSocket.GetTagName());
	CapsuleLength = SocketUtils::GetDistanceBetweenSockets(CashedEnemy->GetSword(), SwordOriginSocket.GetTagName(), SwordLengthSocket.GetTagName());
}

void ASANAS_EController::TickAttackWindow(float FrameDeltaTime)
{
	if (!CashedEnemy)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Cast Failed in AIController"))
		return;
	}
	
	FCollisionQueryParams Params (SCENE_QUERY_STAT(MeleeSweep), false);
	Params.AddIgnoredActor(this);
	Params.AddIgnoredComponent(CashedEnemy->GetSword());
	
	CapsuleOrigin = SocketUtils::GetSocketTransform(CashedEnemy->GetSword(), SwordOriginSocket.GetTagName());
	CapsuleRadius = SocketUtils::GetDistanceBetweenSockets(CashedEnemy->GetSword(), SwordOriginSocket.GetTagName(), SwordRadiusSocket.GetTagName());
	CapsuleLength = SocketUtils::GetDistanceBetweenSockets(CashedEnemy->GetSword(), SwordOriginSocket.GetTagName(), SwordLengthSocket.GetTagName());

	if (!CapsuleRadius.IsSet() || !CapsuleLength.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing sockets for capsule dimensions"))
		return;
	}

	TArray<FHitResult> Hits;
	const FCollisionShape Capsule = FCollisionShape::MakeCapsule(CapsuleRadius.GetValue(), CapsuleLength.GetValue()/2);

	const bool bHit = GetWorld()->SweepMultiByProfile(Hits, CapsuleOrigin->GetLocation(), CapsuleOrigin->GetLocation(), CapsuleOrigin->GetRotation(), TEXT("MeleeTrace"), Capsule, Params);
	DrawDebugCapsule(GetWorld(), CapsuleOrigin->GetLocation(), CapsuleLength.GetValue()/2, CapsuleRadius.GetValue(), CapsuleOrigin->GetRotation(), bHit ? FColor::Green : FColor::Red, false, -1.f, 0, 0.5f);

	if (bHit)
	{
		for (const FHitResult& Hit : Hits)
		{
			if (Hit.GetComponent() == CashedEnemy->GetSword())
				continue;

			if (HitActors.Contains(Hit.GetActor()))
				continue;
			if (Hit.GetActor()->GetClass() == CashedEnemy->GetClass())
				continue;
			
#if WITH_EDITOR
			UE_LOG(LogTemp, Warning, TEXT("HitObject: %s"),*Hit.GetActor()->GetClass()->GetName());
#endif
			
			HitActors.Add(Hit.GetActor());
			
			if (Hit.GetActor() != CashedEnemy)
			{
				CashedEnemy->TryApplyingDamage(Hit.GetActor());	
			}
		}
	}
}

void ASANAS_EController::EndAttackWindow()
{
	HitActors.Reset();
}

// Called when the game starts or when spawned
void ASANAS_EController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree.Get());
		GetBlackboardComponent()->SetValueAsObject(FName("Player"), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}

	ASANAS_BaseEnemy* _Pawn = Cast<ASANAS_BaseEnemy>(GetPawn());

	if (_Pawn)
	{
		//_Pawn->OnEnemyDeath().AddUObject(this, &ASANAS_EController::PawnDied);
	}
	
	ASANAS_Player* Player = Cast<ASANAS_Player>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Player)
	{
		Player->OnPlayerDeath().AddUObject(this, &ASANAS_EController::PlayerDied);
	}
}

void ASANAS_EController::PlayerDied()
{
	Super::PlayerDied();
	GetBlackboardComponent()->SetValueAsBool(FName("PlayerDied"), true);
}

void ASANAS_EController::PawnDied()
{
	GetBlackboardComponent()->SetValueAsBool(FName("SelfDied"), true);
}

// Called every frame
void ASANAS_EController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

