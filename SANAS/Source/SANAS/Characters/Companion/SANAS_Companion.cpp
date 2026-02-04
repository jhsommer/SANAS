// Fill out your copyright notice in the Description page of Project Settings.


#include "SANAS_Companion.h"


// Sets default values
ASANAS_Companion::ASANAS_Companion()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASANAS_Companion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASANAS_Companion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


