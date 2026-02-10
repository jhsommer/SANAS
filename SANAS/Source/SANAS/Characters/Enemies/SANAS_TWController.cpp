// Fill out your copyright notice in the Description page of Project Settings.


#include "SANAS_TWController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SANAS_TwinSwordEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "SANAS/Utils/SockeUtils.h"
#include "SANAS/Characters/Player/SANAS_Player.h"


// Sets default values
ASANAS_TWController::ASANAS_TWController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASANAS_TWController::StartAttackWindow()
{
	Super::StartAttackWindow();
	CashedEnemy= Cast<ASANAS_TwinSwordEnemy>(GetPawn());
	if (!CashedEnemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn Cast Failed in AIController in TW"))
		UE_LOG(LogTemp, Warning, TEXT("Pawn class: %s"),*GetPawn()->GetClass()->GetName());
		return;
	}

	CashedTwinSwordMeshes.Add(CashedEnemy->GetTwinSwordLeft());
	CashedTwinSwordMeshes.Add(CashedEnemy->GetTwinSwordRight());

	for (UStaticMeshComponent* Sword : CashedTwinSwordMeshes)
	{
		CapsuleOrigin = SocketUtils::GetSocketTransform(Sword, SwordOriginSocket);
		CapsuleRadius = SocketUtils::GetDistanceBetweenSockets(Sword, SwordOriginSocket, SwordRadiusSocket);
		CapsuleLength = SocketUtils::GetDistanceBetweenSockets(Sword, SwordOriginSocket, SwordLengthSocket);
	}
	
}

void ASANAS_TWController::TickAttackWindow(float FrameDeltaTime)
{
	Super::TickAttackWindow(FrameDeltaTime);

	if (!CashedEnemy)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Cast Failed in AIController"))
		return;
	}
	
	FCollisionQueryParams Params (SCENE_QUERY_STAT(MeleeSweep), false);
	Params.AddIgnoredActor(this);

	for (UStaticMeshComponent* Sword : CashedTwinSwordMeshes)
	{
		Params.AddIgnoredComponent(Sword);
	
		CapsuleOrigin = SocketUtils::GetSocketTransform(Sword, SwordOriginSocket);
		CapsuleRadius = SocketUtils::GetDistanceBetweenSockets(Sword, SwordOriginSocket, SwordRadiusSocket);
		CapsuleLength = SocketUtils::GetDistanceBetweenSockets(Sword, SwordOriginSocket, SwordLengthSocket);

		if (!CapsuleRadius.IsSet() || !CapsuleLength.IsSet())
		{
			UE_LOG(LogTemp, Warning, TEXT("Missing sockets for capsule dimensions"))
			return;
		}

		TArray<FHitResult> Hits;
		const FCollisionShape Capsule = FCollisionShape::MakeCapsule(CapsuleRadius.GetValue(), CapsuleLength.GetValue()/2);

		const bool bHit = GetWorld()->SweepMultiByProfile(Hits, CapsuleOrigin->GetLocation(), CapsuleOrigin->GetLocation(), CapsuleOrigin->GetRotation(), TEXT("MeleeTrace"), Capsule, Params);

#if WITH_EDITOR
		DrawDebugCapsule(GetWorld(), CapsuleOrigin->GetLocation(), CapsuleLength.GetValue()/2, CapsuleRadius.GetValue(), CapsuleOrigin->GetRotation(), bHit ? FColor::Green : FColor::Red, false, -1.f, 0, 0.5f);
#endif
		if (bHit)
		{
			for (const FHitResult& Hit : Hits)
			{
				if (Hit.GetComponent() == Sword)
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
	
	
}

void ASANAS_TWController::EndAttackWindow()
{
	Super::EndAttackWindow();
	HitActors.Reset();
	CashedTwinSwordMeshes.Reset();
}

// Called when the game starts or when spawned
void ASANAS_TWController::BeginPlay()
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
		Player->OnPlayerDeath().AddUObject(this, &ASANAS_TWController::PlayerDied);
	}
}

void ASANAS_TWController::PlayerDied()
{
	GetBlackboardComponent()->SetValueAsBool(FName("PlayerDied"), true);
}

void ASANAS_TWController::PawnDied()
{
	Super::PawnDied();
	GetBlackboardComponent()->SetValueAsBool(FName("SelfDied"), true);
}

// Called every frame
void ASANAS_TWController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

