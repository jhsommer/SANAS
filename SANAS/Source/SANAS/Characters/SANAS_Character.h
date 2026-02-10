// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SANAS/Interfaces/Damageable.h"
#include "SANAS_Character.generated.h"

class UHealthComponent;

UCLASS()
class SANAS_API ASANAS_Character : public ACharacter, public IDamageable
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ASANAS_Character();

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UHealthComponent> HealthComponent;

	float MaxHealth;
	float CurrentHealth;

	virtual void TryApplyingDamage(AActor* HitActor);
	
};
