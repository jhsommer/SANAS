// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SANAS_BaseEnemy.h"
#include "SANAS_Archer.generated.h"

class UDA_Enemy_Bow;

UCLASS()
class SANAS_API ASANAS_Archer : public ASANAS_BaseEnemy
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon",  meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Bow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon",  meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDA_Enemy_Bow> BowData;
	
public:
	// Sets default values for this character's properties
	ASANAS_Archer();

	UStaticMeshComponent* GetBowComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EnemyDied() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void ReceiveDamage_Implementation(int Damage) override;
	virtual void TryApplyingDamage(AActor* HitActor) override;
};
