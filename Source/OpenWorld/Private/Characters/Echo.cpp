#pragma once

#include "Characters/Echo.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Animation/AnimMontage.h"
#include "Items/Weapons/Weapon.h"


AEcho::AEcho()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEcho::BeginPlay()
{
	Super::BeginPlay();

	if(const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AEcho::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEcho::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEcho::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AEcho::Jump);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AEcho::Interact);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AEcho::Attack);
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &AEcho::Dodge);
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Started, this, &AEcho::Equip);
	}
}

void AEcho::Jump()
{
	Super::Jump();
}

void AEcho::Move(const FInputActionValue& Value)
{
	if(ActionState != ECharacterActionState::Unoccupied)
		return;
	
	if(const FVector2d MovementVector = Value.Get<FVector2d>(); GetController())
	{
		const FRotationMatrix RotationMatrix = FRotationMatrix(GetControlRotation());

		const FVector ForwardDirection = RotationMatrix.GetScaledAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MovementVector.Y);

		const FVector RightDirection = RotationMatrix.GetScaledAxis(EAxis::Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AEcho::Look(const FInputActionValue& Value)
{
	if(const FVector2d LookAxisVector = Value.Get<FVector2d>(); GetController())
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AEcho::Interact(const FInputActionValue& Value)
{
}

void AEcho::Attack(const FInputActionValue& Value)
{
	if(CanAttack())
	{
		PlayAttackMontage();
		ActionState = ECharacterActionState::Attacking;
	}
}

void AEcho::PlayAttackMontage()
{
	if(UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance(); AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);

		if(++AttackMontageIndex >= AttackMontage->CompositeSections.Num())
		{
			AttackMontageIndex = 0;
		}

		const FName SectionName = FName(*("Attack" + FString::FromInt(AttackMontageIndex + 1)));

		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
	}
}

bool AEcho::CanAttack() const
{
	return ActionState == ECharacterActionState::Unoccupied &&
		EquipmentState != ECharacterEquipmentState::Unequipped;
}

void AEcho::OnAttackEnd()
{
	ActionState = ECharacterActionState::Unoccupied;
}

void AEcho::Dodge(const FInputActionValue& Value)
{
}

void AEcho::Equip()
{
	if(AWeapon* Weapon = Cast<AWeapon>(OverlappingItem))
	{
		Weapon->Equip(GetMesh(), RightHandSocketName);
		EquipmentState = ECharacterEquipmentState::OneHanded;
		
		EquippedWeapon = Weapon;
		OverlappingItem = nullptr;
	}
	else
	{
		if(ActionState == ECharacterActionState::Unoccupied)
		{
			if(EquipmentState != ECharacterEquipmentState::Unequipped)
			{
				ActionState = ECharacterActionState::Arming;
				PlayArmingMontage(FName("Disarm"));
				EquipmentState = ECharacterEquipmentState::Unequipped;
			}
			else if(EquipmentState == ECharacterEquipmentState::Unequipped && EquippedWeapon)
			{
				ActionState = ECharacterActionState::Arming;
				PlayArmingMontage(FName("Arm"));
				EquipmentState = ECharacterEquipmentState::OneHanded;
			}
		}
	}
}

void AEcho::PlayArmingMontage(const FName SectionName) const
{
	if(UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance(); AnimInstance && ArmingMontage)
	{
		AnimInstance->Montage_Play(ArmingMontage);
		AnimInstance->Montage_JumpToSection(SectionName, ArmingMontage);
	}
}

void AEcho::OnArm() const
{
	if(EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), RightHandSocketName);
	}
}

void AEcho::OnDisarm() const
{
	if(EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), BackSocketName);
	}
}

void AEcho::OnArmingFinished()
{
	ActionState = ECharacterActionState::Unoccupied;
}



	