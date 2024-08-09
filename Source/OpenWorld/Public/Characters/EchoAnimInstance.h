
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EchoAnimInstance.generated.h"

enum class ECharacterEquipmentState : uint8;
class AEcho;
class UCharacterMovementComponent;

UCLASS()
class OPENWORLD_API UEchoAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	AEcho* Echo;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	UCharacterMovementComponent* EchoMovementComponent;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsFalling;

private:
	ECharacterEquipmentState CharacterEquipmentState;
};
