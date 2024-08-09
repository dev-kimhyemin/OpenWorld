
#include "Characters/Echo.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
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

void AEcho::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
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
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AEcho::Attack);
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &AEcho::Dodge);
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &AEcho::Equip);
	}
}

void AEcho::Jump()
{
	Super::Jump();
}

void AEcho::Move(const FInputActionValue& Value)
{
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
}

void AEcho::Dodge(const FInputActionValue& Value)
{
}

void AEcho::Equip()
{
	if(const AWeapon* Weapon = Cast<AWeapon>(OverlappingItem))
	{
		Weapon->Equip(GetMesh(), RightHandSocketName);
		EquipmentState = ECharacterEquipmentState::Axe;
	}
}


