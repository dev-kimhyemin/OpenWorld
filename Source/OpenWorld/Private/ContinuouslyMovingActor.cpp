// Fill out your copyright notice in the Description page of Project Settings.


#include "ContinuouslyMovingActor.h"

AContinuouslyMovingActor::AContinuouslyMovingActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AContinuouslyMovingActor::BeginPlay()
{
	Super::BeginPlay();
}

void AContinuouslyMovingActor::DrawDebugHelper() const
{
	if(const UWorld* World = GetWorld())
	{
		const FVector Location = GetActorLocation();

		DrawDebugSphere(World, Location, 20.f, 16, FColor::Red, false, 0.05f);
	}
}

void AContinuouslyMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

	AddActorWorldOffset(GetUpdatedOffsetCoordinate(DeltaTime));
	DrawDebugHelper();
}

FVector AContinuouslyMovingActor::GetUpdatedOffsetCoordinate(const float DeltaTime) const
{
	float DeltaX = 0.f;
	float DeltaY = 0.f;
	float DeltaZ = 0.f;

	if(MoveX)
	{
		DeltaX = XValues.Amplitude
			* GetOffsetWithMovementType(XValues.MovementType, DeltaTime, XValues.BounceSpeed);
	}

	if(MoveY)
	{
		DeltaY = YValues.Amplitude
			* GetOffsetWithMovementType(YValues.MovementType, DeltaTime, YValues.BounceSpeed);
	}

	if(MoveZ)
	{
		DeltaZ = ZValues.Amplitude
			* GetOffsetWithMovementType(ZValues.MovementType, DeltaTime, ZValues.BounceSpeed);
	}

	return FVector(DeltaX, DeltaY, DeltaZ);
}

float AContinuouslyMovingActor::GetOffsetWithMovementType(EMovementType MovementType, float DeltaTime, float BounceSpeed) const
{
	switch (MovementType)
	{
		case EMovementType::Linear:
			return DeltaTime;
		
		case EMovementType::SinPingPong:
			return FMath::Sin(RunningTime * BounceSpeed) * DeltaTime;
		
		case EMovementType::CosPingPong:
			return FMath::Cos(RunningTime * BounceSpeed) * DeltaTime;
			
		default:
			return 0.f;
	}
}




