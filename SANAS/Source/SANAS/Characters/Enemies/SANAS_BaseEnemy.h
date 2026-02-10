// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SANAS/Characters/SANAS_Character.h"
#include "SANAS_BaseEnemy.generated.h"

class UEnemyHealthbarWidget;
class UWidgetComponent;
DECLARE_EVENT(ASANAS_BaseEnemy, FEnemyDead);

UCLASS(Abstract)
class SANAS_API ASANAS_BaseEnemy : public ASANAS_Character
{
	GENERATED_BODY()


	
public:
	// Sets default values for this character's properties
	ASANAS_BaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	TObjectPtr<UAnimMontage> DeathAnim;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWidgetComponent> HealthbarWidget;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FEnemyDead& OnEnemyDeath() {return OnEnemyDeathEvent;}

	virtual  void EnemyDied();

protected:
	FEnemyDead OnEnemyDeathEvent;
};
