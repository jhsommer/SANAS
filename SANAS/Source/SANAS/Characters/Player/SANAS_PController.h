// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SANAS_PController.generated.h"

class USANAS_HUD;

UCLASS()
class SANAS_API ASANAS_PController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category= "UI")
	TSubclassOf<USANAS_HUD> HUDClass;
	
	UPROPERTY()
	TObjectPtr<USANAS_HUD> HUD;
	
public:
	// Sets default values for this actor's properties
	ASANAS_PController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
