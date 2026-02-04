// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SANAS/Characters/SANAS_AIController.h"
#include "SANAS_ArcherController.generated.h"

class ASANAS_Archer;
class ASANAS_BaseEnemy;

UCLASS()
class SANAS_API ASANAS_ArcherController : public ASANAS_AIController
{
	GENERATED_BODY()

	FVector TraceStart =  FVector::ZeroVector;
	FVector TraceEnd =  FVector::ZeroVector;

	UPROPERTY()
	ASANAS_Archer* CashedPawn =  nullptr;
	
public:
	// Sets default values for this actor's properties
	ASANAS_ArcherController();

	virtual void StartAttackWindow() override;
	virtual void TickAttackWindow(float FrameDeltaTime) override;
	virtual void EndAttackWindow() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PlayerDied() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Shoot();
};
