// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "GameplayTagContainer.h"
#include "SANAS_AIController.generated.h"



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

	const FName SwordOriginSocket = "Sword.Hitbox.Origin";
	const FName SwordRadiusSocket = "Sword.Hitbox.Radius";
	const FName SwordLengthSocket = "Sword.Hitbox.Length";

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
