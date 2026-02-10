// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthbarWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class SANAS_API UEnemyHealthbarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHealthPercent(float Percent);

protected:
	
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthBar;
};
