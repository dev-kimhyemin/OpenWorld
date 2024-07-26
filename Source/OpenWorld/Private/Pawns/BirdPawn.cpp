// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BirdPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"

constexpr float Tolerance = KINDA_SMALL_NUMBER;


ABirdPawn::ABirdPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
}

void ABirdPawn::BeginPlay()
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

void ABirdPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABirdPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABirdPawn::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABirdPawn::Look);
		EnhancedInputComponent->BindAction(RiseAction, ETriggerEvent::Triggered, this, &ABirdPawn::Rise);
	}
}

void ABirdPawn::Move(const FInputActionValue& Value)
{
	if(const float DirectionValue = Value.Get<float>();
		GetController() && FMath::Abs(DirectionValue) > KINDA_SMALL_NUMBER)
	{
		const FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, DirectionValue);
	}
}

void ABirdPawn::Look(const FInputActionValue& Value)
{
	if(const FVector2d AxisValue = Value.Get<FVector2d>(); GetController())
	{
		AddControllerYawInput(AxisValue.X);
		AddControllerPitchInput(-AxisValue.Y);
	}
}

void ABirdPawn::Rise(const FInputActionValue& Value)
{
	if(const float DirectionValue = Value.Get<float>();
		GetController() && FMath::Abs(DirectionValue) > KINDA_SMALL_NUMBER)
	{
		const FVector Up = GetActorUpVector();
		AddMovementInput(Up, DirectionValue);
	}
}

