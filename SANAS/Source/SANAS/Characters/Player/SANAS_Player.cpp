// Copyright Epic Games, Inc. All Rights Reserved.

#include "SANAS_Player.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "SANAS/Components/HealthComponent.h"
#include "SANAS/Characters/Player/DA_Weapon_Spear.h"
#include "SANAS/Utils/SockeUtils.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ASANAS_Player::ASANAS_Player()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Spear = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spear"));
	Spear->SetupAttachment(GetMesh());
	
}

void ASANAS_Player::BeginPlay()
{
	Super::BeginPlay();
	Spear->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("ik_spear"));
	
}

void ASANAS_Player::StartAttackWindow()
{
	CapsuleOrigin = SocketUtils::GetSocketTransform(Spear.Get(), OriginSocket);
	CapsuleRadius = SocketUtils::GetDistanceBetweenSockets(Spear.Get(), OriginSocket, RadiusSocket);
	CapsuleLength = SocketUtils::GetDistanceBetweenSockets(Spear.Get(), OriginSocket, LengthSocket);
	
}

void ASANAS_Player::TickAttackWindow(float FrameDeltaTime)
{
	FCollisionQueryParams Params (SCENE_QUERY_STAT(MeleeSweep), false);
	Params.AddIgnoredActor(this);
	Params.AddIgnoredComponent(Spear.Get());
	
	CapsuleOrigin = SocketUtils::GetSocketTransform(Spear.Get(), OriginSocket);
	CapsuleRadius = SocketUtils::GetDistanceBetweenSockets(Spear.Get(), OriginSocket, RadiusSocket);
	CapsuleLength = SocketUtils::GetDistanceBetweenSockets(Spear.Get(), OriginSocket, LengthSocket);

	if (!CapsuleRadius.IsSet() || !CapsuleLength.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing sockets for capsule dimensions"))
		return;
	}
			
	TArray<FHitResult> Hits;
	const FCollisionShape Capsule = FCollisionShape::MakeCapsule(CapsuleRadius.GetValue(), CapsuleLength.GetValue()/2);

	const bool bHit = GetWorld()->SweepMultiByProfile(Hits, CapsuleOrigin->GetLocation(), CapsuleOrigin->GetLocation(), CapsuleOrigin->GetRotation(), TEXT("MeleeTrace"), Capsule, Params);

#if WITH_EDITOR
	
	DrawDebugCapsule(GetWorld(), CapsuleOrigin->GetLocation(), CapsuleLength.GetValue()/2, CapsuleRadius.GetValue(), CapsuleOrigin->GetRotation(), bHit ? FColor::Green : FColor::Red, false, -1.f, 0, 0.5f);

#endif
	// for (const  FHitResult& Hit : Hits)
	// {
	// 	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Black, Hit.GetActor()->GetName());
	// }
	
	if (bHit)
	{
		for (const FHitResult& Hit : Hits)
		{
			if (Hit.GetComponent() == Spear.Get())
				continue;

			if (HitActors.Contains(Hit.GetActor()))
				continue;

			HitActors.Add(Hit.GetActor());
			
			if (Hit.GetActor() != GetOwner())
			{
				TryApplyingDamage(Hit.GetActor());	
			}
		}
	}
}

void ASANAS_Player::EndAttackWindow()
{
	HitActors.Reset();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASANAS_Player::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ASANAS_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASANAS_Player::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASANAS_Player::Look);

		//Attacking
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ASANAS_Player::Attack);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ASANAS_Player::PlayerDied()
{
	OnPlayerDeath().Broadcast();
}

void ASANAS_Player::ReceiveDamage_Implementation(int Damage)
{
	Super::ReceiveDamage_Implementation(Damage);

	int TempHealth = HealthComponent->GetHealth() - Damage;
	if (TempHealth <= 0)
	{
		if (DeathAnim)
		{
			GetController()->StopMovement();
			GetController()->SetIgnoreMoveInput(true);
			GetController()->SetIgnoreLookInput(true);
			GetMesh()->PlayAnimation(DeathAnim, false);
		}
		return;
	}
	HealthComponent->SetHealth(TempHealth);
}

void ASANAS_Player::TryApplyingDamage(AActor* HitActor)
{
	Super::TryApplyingDamage(HitActor);
	if(HitActor && HitActor->GetClass()->ImplementsInterface(UDamageable::StaticClass()) && SpearData)
	{
		IDamageable::Execute_ReceiveDamage(HitActor, SpearData->Damage);
	}
	
}

void ASANAS_Player::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASANAS_Player::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASANAS_Player::Attack(const FInputActionValue& Value)
{
	bool AttackInitiated = Value.Get<bool>();

	if (AttackInitiated)
	{
		if (AttackMontage)
		{
			PlayAnimMontage(AttackMontage);
			return;
		}
	}

	GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Black, TEXT("Attack was not recognized"));
}


