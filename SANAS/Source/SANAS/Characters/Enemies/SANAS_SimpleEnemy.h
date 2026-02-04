// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SANAS_BaseEnemy.h"
#include "SANAS/Characters/SANAS_Character.h"
#include "SANAS_SimpleEnemy.generated.h"


class ASANAS_EController;
class UBehaviorTree;

//

class UDA_Enemy_SimpleWeapon;

UCLASS()
class SANAS_API ASANAS_SimpleEnemy : public ASANAS_BaseEnemy
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon",  meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Sword;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDA_Enemy_SimpleWeapon> SimpleWeaponData;

	
public:
	// Sets default values for this character's properties
	ASANAS_SimpleEnemy();

	UStaticMeshComponent* GetSword();
	UDA_Enemy_SimpleWeapon* GetSwordData();
	
	//FEnemyDead& OnEnemyDeath() {return OnEnemyDeathEvent;};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	

private:
	
	//FEnemyDead OnEnemyDeathEvent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void ReceiveDamage_Implementation(int Damage) override;

	virtual void TryApplyingDamage(AActor* HitActor) override;

	virtual  void EnemyDied() override;
	
};
