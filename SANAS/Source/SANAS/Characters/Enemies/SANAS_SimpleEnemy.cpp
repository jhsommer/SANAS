// Fill out your copyright notice in the Description page of Project Settings.


#include "SANAS_SimpleEnemy.h"

#include "SANAS_EController.h"
#include "Components/CapsuleComponent.h"
#include "SANAS/Characters/Enemies/DA_Enemy_SimpleWeapon.h"
#include "SANAS/Components/HealthComponent.h"


// Sets default values
ASANAS_SimpleEnemy::ASANAS_SimpleEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword"));
	Sword->SetupAttachment(GetMesh());
}

UStaticMeshComponent* ASANAS_SimpleEnemy::GetSword()
{
	if (Sword)
	{
		return Sword.Get();
	}

	UE_LOG(LogTemp, Warning, TEXT("GetSword: Sword=%s"), *GetNameSafe(Sword));
	return nullptr;
}

UDA_Enemy_SimpleWeapon* ASANAS_SimpleEnemy::GetSwordData()
{
	return SimpleWeaponData;
}

// Called when the game starts or when spawned
void ASANAS_SimpleEnemy::BeginPlay()
{
	Super::BeginPlay();
	Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("ik_sword"));
}

void ASANAS_SimpleEnemy::TryApplyingDamage(AActor* HitActor)
{
	Super::TryApplyingDamage(HitActor);

	if(HitActor && HitActor->GetClass()->ImplementsInterface(UDamageable::StaticClass()) && SimpleWeaponData)
	{
		IDamageable::Execute_ReceiveDamage(HitActor, SimpleWeaponData->Damage);
	}
}

void ASANAS_SimpleEnemy::ReceiveDamage_Implementation(int Damage)
{
	Super::ReceiveDamage_Implementation(Damage);

	int TempHealth = HealthComponent->GetHealth() - Damage;
	
	if (TempHealth <= 0)
	{
		if (DeathAnim)
		{
			//Animation wird interrupted. Warum???
			ASANAS_EController* MyController = Cast<ASANAS_EController>(GetController());
			if (MyController)
			{
				MyController->PawnDied();
			}
			PlayAnimMontage(DeathAnim.Get());
		}
		return;
	}
	HealthComponent->SetHealth(TempHealth);

	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Black,  FString::Printf(TEXT("Damage: %d"), Damage));
}

void ASANAS_SimpleEnemy::EnemyDied()
{
	OnEnemyDeathEvent.Broadcast();
	Destroy();
}

// Called every frame
void ASANAS_SimpleEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


