// Fill out your copyright notice in the Description page of Project Settings.


#include "SANAS_ArcherController.h"

#include "SANAS_Archer.h"
#include "SANAS_BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "SANAS/Characters/Player/SANAS_Player.h"


// Sets default values
ASANAS_ArcherController::ASANAS_ArcherController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASANAS_ArcherController::StartAttackWindow()
{
	Super::StartAttackWindow();
	
	CashedPawn = Cast<ASANAS_Archer>(GetPawn());

	if (!CashedPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Pawn in Archer Controller"));
		return;
	}
	
	TraceStart = GetPawn()->GetActorLocation();
	TraceEnd = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation();
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Cyan, false, 3.f, 0, 10.0f);
}

void ASANAS_ArcherController::TickAttackWindow(float FrameDeltaTime)
{
	Super::TickAttackWindow(FrameDeltaTime);
}

void ASANAS_ArcherController::EndAttackWindow()
{
	Super::EndAttackWindow();
	Shoot();
}

// Called when the game starts or when spawned
void ASANAS_ArcherController::BeginPlay()
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
		Player->OnPlayerDeath().AddUObject(this, &ASANAS_ArcherController::PlayerDied);
	}
	
}

void ASANAS_ArcherController::PlayerDied()
{
	Super::PlayerDied();
}

// Called every frame
void ASANAS_ArcherController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASANAS_ArcherController::Shoot()
{
	FCollisionQueryParams TraceParams (SCENE_QUERY_STAT(ArcherShot), false);

	// ASANAS_BaseEnemy* CashedPawnParent = Cast<ASANAS_BaseEnemy>(GetPawn());
	// if (!CashedPawnParent)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Cast to Parent Class failed"));
	// 	return;
	// }
	TraceParams.AddIgnoredActor(CashedPawn);
	FHitResult HitResult;
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams);

	if (bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Player"));
		CashedPawn->TryApplyingDamage(HitResult.GetActor());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Not Valid Hit"));
}

