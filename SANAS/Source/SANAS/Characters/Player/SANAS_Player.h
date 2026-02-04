// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "SANAS/Characters/SANAS_Character.h"
#include "SANAS_Player.generated.h"

struct FGameplayTag;
class UDA_Weapon_Spear;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_EVENT(ASANAS_Player, FPlayerDead);

const FGameplayTag OriginSocket = FGameplayTag::RequestGameplayTag(TEXT("Spear.Hitbox.Origin"));
const FGameplayTag RadiusSocket = FGameplayTag::RequestGameplayTag(TEXT("Spear.Hitbox.Radius"));
const FGameplayTag LengthSocket = FGameplayTag::RequestGameplayTag(TEXT("Spear.Hitbox.Length"));


DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ASANAS_Player : public ASANAS_Character
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon",  meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Spear;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDA_Weapon_Spear> SpearData;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY()
	TSet<TWeakObjectPtr<AActor>> HitActors;

	UPROPERTY(EditDefaultsOnly, Category= "Animation")
	TObjectPtr<UAnimationAsset> DeathAnim;

	TOptional<FTransform> CapsuleOrigin;
	TOptional<float> CapsuleRadius;
	TOptional<float> CapsuleLength;

	FPlayerDead OnPlayerDeathEvent;

public:
	ASANAS_Player();
	virtual void BeginPlay() override;

	void StartAttackWindow();

	void TickAttackWindow(float FrameDeltaTime);

	void EndAttackWindow();

	FPlayerDead& OnPlayerDeath() {return OnPlayerDeathEvent;};

	void PlayerDied();
	

protected:
	//////////////////////////////////////////////////////////////////////////
	// Input
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Attack(const FInputActionValue& Value);

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void ReceiveDamage_Implementation(int Damage) override;
	virtual void TryApplyingDamage(AActor* HitActor) override;
};