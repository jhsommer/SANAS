// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthbarWidget.h"

#include "Components/ProgressBar.h"

void UEnemyHealthbarWidget::SetHealthPercent(float Percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(FMath::Clamp(Percent, 0.f, 1.f));
	}
}
