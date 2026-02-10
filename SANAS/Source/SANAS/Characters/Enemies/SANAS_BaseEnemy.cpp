// Fill out your copyright notice in the Description page of Project Settings.


#include "SANAS_BaseEnemy.h"

#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASANAS_BaseEnemy::ASANAS_BaseEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthbarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Healthbar"));
	HealthbarWidget->SetupAttachment(GetMesh());
	HealthbarWidget->SetWidgetSpace(EWidgetSpace::World);
	HealthbarWidget->SetRelativeLocation(FVector(0.f, 0.f, 120.f));
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
	HealthbarWidget->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(HealthbarWidget->GetComponentLocation(), UGameplayStatics::GetPlayerCameraManager(this, 0)->GetCameraLocation()));
}


void ASANAS_BaseEnemy::EnemyDied()
{
	
}

