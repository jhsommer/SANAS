// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SANAS_HUD.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class SANAS_API USANAS_HUD : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;
	
	int PlayerPoints;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
private:
	UFUNCTION()
	void UpdatePlayerPoints(int NewScore);

	UFUNCTION()
	void UpdateScoreText() ;

	UFUNCTION(BlueprintPure)
	FText GetScoreText() const;
};
