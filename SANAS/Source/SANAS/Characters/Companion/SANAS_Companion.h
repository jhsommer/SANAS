// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SANAS/Characters/SANAS_Character.h"
#include "SANAS_Companion.generated.h"

UCLASS()
class SANAS_API ASANAS_Companion : public ASANAS_Character
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASANAS_Companion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
