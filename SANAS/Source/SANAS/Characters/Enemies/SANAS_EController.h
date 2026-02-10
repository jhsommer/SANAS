// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SANAS/Characters/SANAS_AIController.h"
#include "SANAS_EController.generated.h"

class ASANAS_BaseEnemy;
class UDA_Enemy_SimpleWeapon;
class ASANAS_SimpleEnemy;
struct FGameplayTag;


UCLASS()
class SANAS_API ASANAS_EController : public ASANAS_AIController
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<ASANAS_SimpleEnemy> CashedEnemy = nullptr;
	
public:
	// Sets default values for this actor's properties
	ASANAS_EController();

	virtual void StartAttackWindow() override;

	virtual  void TickAttackWindow(float FrameDeltaTime) override;

	virtual void EndAttackWindow() override;

	virtual void PawnDied() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PlayerDied() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
