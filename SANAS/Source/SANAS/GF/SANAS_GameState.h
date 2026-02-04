// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SANAS_GameState.generated.h"

DECLARE_EVENT_OneParam(ASANAS_GameState, FUpdatePlayerScore, int);

class ASANAS_SimpleEnemy;
/**
 * 
 */

UENUM()
namespace EWave
{
	enum Type : int
	{
		First,
		Second,
		Third,
		Fourth,
		Fifth,
		End
	};
}


UCLASS()
class SANAS_API ASANAS_GameState : public AGameStateBase
{
	GENERATED_BODY()
	
	


	public:
	
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type reason) override;
	
	int GetPlayerScore() const;
	FUpdatePlayerScore& OnUpdatePlayerScore() {return UpdatePlayerScoreEvent;}

	protected:
	void IncrementPlayerScore();
	void PlayerDied();

private:
	int PlayerScore;
	EWave::Type CurrentWave =  EWave::First;
	
	void HandleActorSpawn(AActor* SpawnedActor);
	FDelegateHandle OnActorSpawnedHandle;

	FUpdatePlayerScore UpdatePlayerScoreEvent;
};

