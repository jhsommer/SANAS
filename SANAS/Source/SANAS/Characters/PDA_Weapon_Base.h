// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_Weapon_Base.generated.h"

/**
 * 
 */
UCLASS()
class SANAS_API UPDA_Weapon_Base : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	int Damage;
	
	UPROPERTY(EditAnywhere)
	int StaminaCost;
};
