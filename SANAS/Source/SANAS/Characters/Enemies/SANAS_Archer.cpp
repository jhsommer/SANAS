// Fill out your copyright notice in the Description page of Project Settings.


#include "SANAS_Archer.h"
#include "DA_Enemy_Bow.h"
#include "SANAS/Components/HealthComponent.h"
#include "SANAS/Characters/SANAS_AIController.h"


// Sets default values
ASANAS_Archer::ASANAS_Archer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Bow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bow"));
	Bow->SetupAttachment(GetMesh());
}

UStaticMeshComponent* ASANAS_Archer::GetBowComponent()
{
	return Bow;
}

// Called when the game starts or when spawned
void ASANAS_Archer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASANAS_Archer::EnemyDied()
{
	Super::EnemyDied();
	OnEnemyDeathEvent.Broadcast();
	Destroy();
	
}

// Called every frame
void ASANAS_Archer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASANAS_Archer::ReceiveDamage_Implementation(int Damage)
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

	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Black,  FString::Printf(TEXT("Damage: %d"), Damage));
}

void ASANAS_Archer::TryApplyingDamage(AActor* HitActor)
{
	Super::TryApplyingDamage(HitActor);

	if(HitActor && HitActor->GetClass()->ImplementsInterface(UDamageable::StaticClass()) && BowData)
	{
		IDamageable::Execute_ReceiveDamage(HitActor, BowData->Damage);
	}
}

