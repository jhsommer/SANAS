// Fill out your copyright notice in the Description page of Project Settings.


#include "SANAS_TwinSwordEnemy.h"
#include "DA_Enemy_TwinSwords.h"
#include "SANAS/Characters/SANAS_AIController.h"
#include "SANAS/Components/HealthComponent.h"


// Sets default values
ASANAS_TwinSwordEnemy::ASANAS_TwinSwordEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TwinSwordLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TwinSwordLeft"));
	TwinSwordLeft->SetupAttachment(GetMesh());
	
	TwinSwordRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TwinSwordRight"));
	TwinSwordRight->SetupAttachment(GetMesh());
}

UStaticMeshComponent* ASANAS_TwinSwordEnemy::GetTwinSwordLeft()
{
	if (!IsValid(TwinSwordLeft))
	{
		UE_LOG(LogTemp, Error, TEXT("TwinSwordEnemy: TwinSwordLeft is invalid"));
		return  nullptr;
	}
	
	return TwinSwordLeft;
}

UStaticMeshComponent* ASANAS_TwinSwordEnemy::GetTwinSwordRight()
{
	if (!IsValid(TwinSwordRight))
	{
		UE_LOG(LogTemp, Error, TEXT("TwinSwordEnemy: TwinSwordRight is invalid"));
		return nullptr;
	}
	
	return TwinSwordRight;
}

// Called when the game starts or when spawned
void ASANAS_TwinSwordEnemy::BeginPlay()
{
	Super::BeginPlay();

	USkeletalMeshComponent* MeshComp = GetMesh();
	if (!IsValid(MeshComp))
	{
		UE_LOG(LogTemp, Error, TEXT("TwinSwordEnemy: MeshComp is invalid"));
		return;
	}
	
	if (!IsValid(TwinSwordRight))
	{
		UE_LOG(LogTemp, Error, TEXT("TwinSwordEnemy: TwinSwordRight is invalid"));
		return;
	}
	
	if (!IsValid(TwinSwordLeft))
	{
		UE_LOG(LogTemp, Error, TEXT("TwinSwordEnemy: TwinSwordLeft is invalid"));
		return;
	}
	
	TwinSwordRight->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("ik_sword"));
	TwinSwordLeft->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("ik_sword_r"));
	
}

void ASANAS_TwinSwordEnemy::EnemyDied()
{
	Super::EnemyDied();

	OnEnemyDeathEvent.Broadcast();
	Destroy();
}

void ASANAS_TwinSwordEnemy::TryApplyingDamage(AActor* HitActor)
{
	Super::TryApplyingDamage(HitActor);

	if(HitActor && HitActor->GetClass()->ImplementsInterface(UDamageable::StaticClass()) && TwinSwordsData)
	{
		IDamageable::Execute_ReceiveDamage(HitActor, TwinSwordsData->Damage/2);
	}
}

void ASANAS_TwinSwordEnemy::ReceiveDamage_Implementation(int Damage)
{
	Super::ReceiveDamage_Implementation(Damage);

	int TempHealth = HealthComponent->GetHealth() - Damage;
	
	if (TempHealth <= 0)
	{
		if (DeathAnim)
		{
			//Animation wird interrupted. Warum???
			ASANAS_AIController* MyController = Cast<ASANAS_AIController>(GetController());
			if (MyController)
			{
				MyController->PawnDied();
			}
			PlayAnimMontage(DeathAnim.Get());
		}
		return;
	}
	HealthComponent->SetHealth(TempHealth);
}

// Called every frame
void ASANAS_TwinSwordEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

