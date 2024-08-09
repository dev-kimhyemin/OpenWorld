// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Echo.generated.h"

class UInputMappingContext;
class UInputAction;
class ACollectableItem;

UENUM(BlueprintType)
enum class ECharacterEquipmentState : uint8
{
	Unequipped	UMETA(DisplayName = "Unequipped"),
	Axe			UMETA(DisplayName = "Axe"),
};

UCLASS()
class OPENWORLD_API AEcho : public ACharacter
{
	GENERATED_BODY()

public:
	AEcho();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

protected:
	virtual void BeginPlay() override;

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

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void Dodge(const FInputActionValue& Value);
	void Equip();

	UPROPERTY(VisibleInstanceOnly)
	ACollectableItem* OverlappingItem;

	ECharacterEquipmentState EquipmentState = ECharacterEquipmentState::Unequipped;
	const FName RightHandSocketName = FName("RightHandSocket");

public:
	FORCEINLINE void SetOverlappingItem(ACollectableItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterEquipmentState GetCharacterEquipmentState() const { return EquipmentState; }
};
