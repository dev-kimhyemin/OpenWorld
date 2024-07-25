// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Pawns/BirdPawn.h"

ABirdPawn::ABirdPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
}

void ABirdPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABirdPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void ABirdPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

