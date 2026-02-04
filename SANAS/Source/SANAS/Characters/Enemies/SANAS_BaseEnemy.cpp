// Fill out your copyright notice in the Description page of Project Settings.


#include "SANAS_BaseEnemy.h"


// Sets default values
ASANAS_BaseEnemy::ASANAS_BaseEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASANAS_BaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASANAS_BaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ASANAS_BaseEnemy::EnemyDied()
{
	
}

