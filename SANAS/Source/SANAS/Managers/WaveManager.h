// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SANAS/GF/SANAS_GameState.h"
#include "WaveManager.generated.h"

class ASANAS_Archer;
class ASANAS_TwinSwordEnemy;
class ASANAS_BaseEnemy;
class ASANAS_SimpleEnemy;

UCLASS()
class SANAS_API AWaveManager : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<ASANAS_BaseEnemy*> Enemies;

	UPROPERTY(EditDefaultsOnly)
	FTransform EnemiesSpawnLocation;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASANAS_SimpleEnemy>SimpleEnemyClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASANAS_TwinSwordEnemy> TwinSwordEnemyClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASANAS_Archer> ArcherEnemyClass;
	
	EWave::Type CurrentWave = EWave::First;
	
public:
	// Sets default values for this actor's properties
	AWaveManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void AreEnemiesAlive();

	void RecountEnemies();
	
	void SpawnEnemies();
};
