// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EchoAttributes.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Echo.generated.h"

class UEchoAnimInstance;
class UInputMappingContext;
class UInputAction;
class ACollectableItem;
class UAnimMontage;
class AWeapon;


UCLASS()
class OPENWORLD_API AEcho : public ACharacter
{
	GENERATED_BODY()

public:
	AEcho();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnAttackEnd();
	
	UFUNCTION(BlueprintCallable)
	void OnArm() const;

	UFUNCTION(BlueprintCallable)
	void OnDisarm() const;

	UFUNCTION(BlueprintCallable)
	void OnArmingFinished();

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* DodgeAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* EquipAction;

	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* AttackMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = Montage)
	UAnimMontage* ArmingMontage;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void Dodge(const FInputActionValue& Value);
	void Equip();

	void PlayAttackMontage();
	void PlayArmingMontage(const FName SectionName) const;
	
	bool CanAttack() const;

	UPROPERTY(VisibleInstanceOnly)
	ACollectableItem* OverlappingItem;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AWeapon* EquippedWeapon;

	ECharacterEquipmentState EquipmentState = ECharacterEquipmentState::Unequipped;
	ECharacterActionState ActionState = ECharacterActionState::Unoccupied;
	
	const FName RightHandSocketName = FName("RightHandSocket");
	const FName BackSocketName = FName("BackSocket");

	int32 AttackMontageIndex = 0;

public:
	FORCEINLINE void SetOverlappingItem(ACollectableItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterEquipmentState GetCharacterEquipmentState() const { return EquipmentState; }
};
