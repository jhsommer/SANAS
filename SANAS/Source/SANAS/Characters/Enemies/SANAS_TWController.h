// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SANAS/Characters/SANAS_AIController.h"
#include "SANAS_TWController.generated.h"


class ASANAS_TwinSwordEnemy;

UCLASS()
class SANAS_API ASANAS_TWController : public ASANAS_AIController
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<ASANAS_TwinSwordEnemy> CashedEnemy = nullptr;

	UPROPERTY()
	TArray<UStaticMeshComponent*> CashedTwinSwordMeshes;
	
public:
	// Sets default values for this actor's properties
	ASANAS_TWController();

	virtual void StartAttackWindow() override;
	virtual void TickAttackWindow(float FrameDeltaTime) override;
	virtual void EndAttackWindow() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PlayerDied() override;
	virtual void PawnDied() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
