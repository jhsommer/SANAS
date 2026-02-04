// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "GameplayTagContainer.h"
#include "SANAS_AIController.generated.h"

const FGameplayTag SwordOriginSocket = FGameplayTag::RequestGameplayTag(TEXT("Sword.Hitbox.Origin"));
const FGameplayTag SwordRadiusSocket = FGameplayTag::RequestGameplayTag(TEXT("Sword.Hitbox.Radius"));
const FGameplayTag SwordLengthSocket = FGameplayTag::RequestGameplayTag(TEXT("Sword.Hitbox.Length"));

UCLASS(Abstract)
class SANAS_API ASANAS_AIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY()
	TSet<TWeakObjectPtr<AActor>> HitActors;
	
	TOptional<FTransform> CapsuleOrigin;
	TOptional<float> CapsuleRadius;
	TOptional<float> CapsuleLength;

public:
	// Sets default values for this actor's properties
	ASANAS_AIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PawnDied();
	virtual void StartAttackWindow();
	virtual void TickAttackWindow(float FrameDeltaTime);
	virtual void EndAttackWindow();
	virtual void PlayerDied();
};
