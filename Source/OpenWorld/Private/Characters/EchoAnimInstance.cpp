#pragma once

#include "Characters/EchoAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/Echo.h"

void UEchoAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Echo = Cast<AEcho>(TryGetPawnOwner());

	if(Echo)
	{
		EchoMovementComponent = Echo->GetCharacterMovement();
	}
}

void UEchoAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(EchoMovementComponent)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(EchoMovementComponent->Velocity);
		IsFalling = EchoMovementComponent->IsFalling();
		CharacterEquipmentState = Echo->GetCharacterEquipmentState();
	}
}
