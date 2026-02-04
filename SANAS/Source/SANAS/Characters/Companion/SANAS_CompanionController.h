// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SANAS/Characters/SANAS_AIController.h"
#include "SANAS_CompanionController.generated.h"

UCLASS()
class SANAS_API ASANAS_CompanionController : public ASANAS_AIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASANAS_CompanionController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
