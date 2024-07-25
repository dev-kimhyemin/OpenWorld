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

void AContinuouslyMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;

	AddActorWorldOffset(GetUpdatedOffsetCoordinate(DeltaTime));
	AddActorWorldRotation(GetUpdatedRotatorCoordinate(DeltaTime));
}

FVector AContinuouslyMovingActor::GetUpdatedOffsetCoordinate(const float DeltaTime) const
{
	float DeltaX = 0.f;
	float DeltaY = 0.f;
	float DeltaZ = 0.f;

	if(MoveX)
	{
		DeltaX = GetUpdatedOffsetPoint(XMovementValues, DeltaTime);
	}

	if(MoveY)
	{
		DeltaY = GetUpdatedOffsetPoint(YMovementValues, DeltaTime);
	}

	if(MoveZ)
	{
		DeltaZ = GetUpdatedOffsetPoint(ZMovementValues, DeltaTime);
	}

	return FVector(DeltaX, DeltaY, DeltaZ);
}

FRotator AContinuouslyMovingActor::GetUpdatedRotatorCoordinate(const float DeltaTime) const
{
	float DeltaX = 0.f;
	float DeltaY = 0.f;
	float DeltaZ = 0.f;

	if(RotateX)
	{
		DeltaX = GetUpdatedOffsetPoint(XRotationValues, DeltaTime);
	}

	if(RotateY)
	{
		DeltaY = GetUpdatedOffsetPoint(YRotationValues, DeltaTime);
	}

	if(RotateZ)
	{
		DeltaZ = GetUpdatedOffsetPoint(ZRotationValues, DeltaTime);
	}
	
	return FRotator(DeltaX, DeltaY, DeltaZ);
}

float AContinuouslyMovingActor::GetUpdatedOffsetPoint(const FMovementValues MovementValues, const float DeltaTime) const
{
	return MovementValues.Amplitude
		* GetOffsetWithMovementType(MovementValues.MovementType, DeltaTime, MovementValues.BounceSpeed);
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




