// Fill out your copyright notice in the Description page of Project Settings.


#include "SANAS_Character.h"

#include "SANAS/Components/HealthComponent.h"


// Sets default values
ASANAS_Character::ASANAS_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	
}

void ASANAS_Character::TryApplyingDamage(AActor* HitActor)
{
	
}


