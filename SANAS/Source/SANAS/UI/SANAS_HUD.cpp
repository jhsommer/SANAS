// Fill out your copyright notice in the Description page of Project Settings.


#include "SANAS_HUD.h"

#include "Components/TextBlock.h"
#include "SANAS/GF/SANAS_GameState.h"

void USANAS_HUD::NativeConstruct()
{
	Super::NativeConstruct();

	ASANAS_GameState* GameState = Cast<ASANAS_GameState>(GetWorld()->GetGameState());
	GameState->OnUpdatePlayerScore().AddUFunction(this, FName("UpdatePlayerPoints"));
	
	
	PlayerPoints = GameState->GetPlayerScore();
	UpdateScoreText();
}

void USANAS_HUD::NativeDestruct()
{
	ASANAS_GameState* GameState = Cast<ASANAS_GameState>(GetWorld()->GetGameState());

	if (GameState)
	{
		GameState->OnUpdatePlayerScore().RemoveAll(this);
	}
	
	Super::NativeDestruct();
}

void USANAS_HUD::UpdatePlayerPoints(int NewScore)
{
	PlayerPoints = NewScore;
	UpdateScoreText();
}

void USANAS_HUD::UpdateScoreText() 
{
	if (!IsValid(ScoreText))
	{
		UE_LOG(LogTemp, Warning, TEXT("ScoreText is not valid (widget not constructed yet?)"));
		return;
	}
	
	ScoreText->SetText(GetScoreText());
}


FText USANAS_HUD::GetScoreText() const
{
	return FText::AsNumber(PlayerPoints);
}


