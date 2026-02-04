// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SANAS_BaseEnemy.h"
#include "SANAS_TwinSwordEnemy.generated.h"

class UDA_Enemy_TwinSwords;

UCLASS()
class SANAS_API ASANAS_TwinSwordEnemy : public ASANAS_BaseEnemy
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta =(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> TwinSwordLeft;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta =(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> TwinSwordRight;

	UPROPERTY(EditDefaultsOnly, Category="Weapon Data")
	TObjectPtr<UDA_Enemy_TwinSwords> TwinSwordsData;
	
public:
	// Sets default values for this character's properties
	ASANAS_TwinSwordEnemy();
	UStaticMeshComponent* GetTwinSwordLeft();
	UStaticMeshComponent* GetTwinSwordRight();

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
