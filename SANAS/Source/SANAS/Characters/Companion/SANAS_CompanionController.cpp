// Fill out your copyright notice in the Description page of Project Settings.


#include "SANAS_CompanionController.h"


// Sets default values
ASANAS_CompanionController::ASANAS_CompanionController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASANAS_CompanionController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASANAS_CompanionController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

