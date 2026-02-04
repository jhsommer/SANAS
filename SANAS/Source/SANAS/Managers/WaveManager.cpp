// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "SANAS/Characters/Enemies/SANAS_Archer.h"
#include "SANAS/Characters/Enemies/SANAS_SimpleEnemy.h"
#include "SANAS/Characters/Enemies/SANAS_TwinSwordEnemy.h"

// Sets default values
AWaveManager::AWaveManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnEnemies();
}

// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWaveManager::AreEnemiesAlive() 
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,  FString::Printf(TEXT("Enemies alive!")));
	
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AWaveManager::RecountEnemies);
}

void AWaveManager::RecountEnemies()
{
	Enemies.Empty();
	
	for (TActorIterator<ASANAS_BaseEnemy> It(GetWorld());  It; ++It)
	{
		ASANAS_BaseEnemy* Enemy = *It;
		
		if (IsValid(Enemy) && !Enemy->IsPendingKillPending() && !Enemy->IsActorBeingDestroyed())
		{
			Enemies.Add(Enemy);
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue,  FString::Printf(TEXT("Still Enemies Available")));
		}
		
	}

	if(Enemies.IsEmpty())
	{
		switch (CurrentWave)
		{
		case EWave::First:
			CurrentWave =  EWave::Second;
			break;

		case EWave::Second:
			CurrentWave =  EWave::Third;
			break;

		case EWave::Third:
			CurrentWave =  EWave::Fourth;
			break;

		case EWave::Fourth:
			CurrentWave =  EWave::Fifth;
			break;

		case EWave::Fifth:
			CurrentWave = EWave::End;
			break;

		default:
			break;
		}
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,  FString::Printf(TEXT("Enemies dead!")));
		SpawnEnemies();
	}
}

void AWaveManager::SpawnEnemies()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	switch (CurrentWave)
	{
	case EWave::First:
		// for (int i = 0; i < 3; i++)
		// {
		// 	ASANAS_SimpleEnemy* EnemyToSpawn = GetWorld()->SpawnActorDeferred<ASANAS_SimpleEnemy>(SimpleEnemyClass, EnemiesSpawnLocation,nullptr,nullptr, SpawnInfo.SpawnCollisionHandlingOverride);
		// 	//Set Values of the Enemies depending on the wave
		// 	UGameplayStatics::FinishSpawningActor(EnemyToSpawn,  EnemiesSpawnLocation);
		// }

		// for (int i = 0; i < 2; i++)
		// {
		// 	ASANAS_TwinSwordEnemy* EnemyToSpawn = GetWorld()->SpawnActorDeferred<ASANAS_TwinSwordEnemy>(TwinSwordEnemyClass, EnemiesSpawnLocation,nullptr,nullptr, SpawnInfo.SpawnCollisionHandlingOverride);
		// 	//Set Values of the Enemies depending on the wave
		// 	UGameplayStatics::FinishSpawningActor(EnemyToSpawn,  EnemiesSpawnLocation);
		// }

		for (int i = 0; i < 2; i++)
		{
			ASANAS_Archer* EnemyToSpawn = GetWorld()->SpawnActorDeferred<ASANAS_Archer>(ArcherEnemyClass, EnemiesSpawnLocation,nullptr,nullptr, SpawnInfo.SpawnCollisionHandlingOverride);
			//Set Values of the Enemies depending on the wave
			UGameplayStatics::FinishSpawningActor(EnemyToSpawn,  EnemiesSpawnLocation);
		}
		break;

	case EWave::Second:
		for (int i = 0; i < 2; i++)
		{
			ASANAS_SimpleEnemy* EnemyToSpawn = GetWorld()->SpawnActorDeferred<ASANAS_SimpleEnemy>(SimpleEnemyClass, EnemiesSpawnLocation);
			//Set Values of the Enemies depending on the wave
			UGameplayStatics::FinishSpawningActor(EnemyToSpawn,  EnemiesSpawnLocation);
		}
		break;

	case EWave::Third:
		for (int i = 0; i < 4; i++)
		{
			ASANAS_SimpleEnemy* EnemyToSpawn = GetWorld()->SpawnActorDeferred<ASANAS_SimpleEnemy>(SimpleEnemyClass, EnemiesSpawnLocation);
			//Set Values of the Enemies depending on the wave
			UGameplayStatics::FinishSpawningActor(EnemyToSpawn,  EnemiesSpawnLocation);
		}
		break;

	case EWave::Fourth:
		for (int i = 0; i < 8; i++)
		{
			ASANAS_SimpleEnemy* EnemyToSpawn = GetWorld()->SpawnActorDeferred<ASANAS_SimpleEnemy>(SimpleEnemyClass, EnemiesSpawnLocation);
			//Set Values of the Enemies depending on the wave
			UGameplayStatics::FinishSpawningActor(EnemyToSpawn,  EnemiesSpawnLocation);
		}
		break;

	case EWave::Fifth:
		for (int i = 0; i < 8; i++)
		{
			ASANAS_SimpleEnemy* EnemyToSpawn = GetWorld()->SpawnActorDeferred<ASANAS_SimpleEnemy>(SimpleEnemyClass, EnemiesSpawnLocation);
			//Set Values of the Enemies depending on the wave
			UGameplayStatics::FinishSpawningActor(EnemyToSpawn,  EnemiesSpawnLocation);
		}
		break;

	default:
		break;
	}

	for (TActorIterator<ASANAS_BaseEnemy> It(GetWorld());  It; ++It)
	{
		Enemies.Add(*It);
		It->OnEnemyDeath().AddUFunction(this, "AreEnemiesAlive");
	}
}

