// Fill out your copyright notice in the Description page of Project Settings.


#include "SANAS_AIController.h"


// Sets default values
ASANAS_AIController::ASANAS_AIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASANAS_AIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASANAS_AIController::StartAttackWindow()
{
}

void ASANAS_AIController::TickAttackWindow(float FrameDeltaTime)
{
}

void ASANAS_AIController::EndAttackWindow()
{
}

void ASANAS_AIController::PlayerDied()
{
}

// Called every frame
void ASANAS_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASANAS_AIController::PawnDied()
{
}

