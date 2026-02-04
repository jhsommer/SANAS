// Fill out your copyright notice in the Description page of Project Settings.


#include "SANAS_PController.h"
#include "SANAS/UI/SANAS_HUD.h"


// Sets default values
ASANAS_PController::ASANAS_PController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASANAS_PController::BeginPlay()
{
	Super::BeginPlay();

	if (!HUDClass)
	{
		UE_LOG(LogTemp, Error, TEXT("HUDWidgetClass not set"));
		return;
	}
	
	HUD = CreateWidget<USANAS_HUD>(this, HUDClass);
	if (!HUD)
	{
		UE_LOG(LogTemp, Error, TEXT(" Failed to create HUDWidget"));
		return;
	}

	HUD->AddToViewport();
	HUD->SetVisibility(ESlateVisibility::HitTestInvisible);
}

// Called every frame
void ASANAS_PController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

