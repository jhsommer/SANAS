// Fill out your copyright notice in the Description page of Project Settings.


#include "SANAS_GameState.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "SANAS/Characters/Enemies/SANAS_SimpleEnemy.h"
#include "SANAS/Characters/Player/SANAS_Player.h"


void ASANAS_GameState::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ASANAS_SimpleEnemy> It(GetWorld());  It; ++It)
	{
		It->OnEnemyDeath().AddUObject(this, &ASANAS_GameState::IncrementPlayerScore);
	}

	OnActorSpawnedHandle = GetWorld()->AddOnActorSpawnedHandler(FOnActorSpawned::FDelegate::CreateUObject(this, &ASANAS_GameState::HandleActorSpawn));

	ASANAS_Player* Player = Cast<ASANAS_Player>(UGameplayStatics::GetPlayerCharacter(this, 0));
	Player->OnPlayerDeath().AddUObject(this, &ASANAS_GameState::PlayerDied);
}

void ASANAS_GameState::EndPlay(const EEndPlayReason::Type reason)
{
	if (const UWorld* World = GetWorld())
	{
		World->RemoveOnActorSpawnedHandler(OnActorSpawnedHandle);
	}
	
	Super::EndPlay(reason);
}

int ASANAS_GameState::GetPlayerScore() const
{
	return PlayerScore;
}

void ASANAS_GameState::IncrementPlayerScore()
{
	PlayerScore++;
	UpdatePlayerScoreEvent.Broadcast(PlayerScore);
}

void ASANAS_GameState::PlayerDied()
{
	UGameplayStatics::OpenLevel(this, FName(GetLevel()->GetName()));
}

void ASANAS_GameState::HandleActorSpawn(AActor* SpawnedActor)
{
	if (!IsValid(SpawnedActor) || SpawnedActor->GetWorld() != GetWorld())
		return;

	if (ASANAS_SimpleEnemy* Enemy = Cast<ASANAS_SimpleEnemy>(SpawnedActor))
	{
		Enemy->OnEnemyDeath().AddUObject(this, &ASANAS_GameState::IncrementPlayerScore);
	}
}
