// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ContinuouslyMovingActor.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Linear		UMETA(DisplayName="Linear"),
	SinPingPong	UMETA(DisplayName="SinPingPong"),
	CosPingPong	UMETA(DisplayName="CosPingPong")
};

USTRUCT(Blueprintable)
struct FMovementValues
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EMovementType MovementType;

	UPROPERTY(EditAnywhere, meta=(ClampMin=0.f))
	float Amplitude;

	UPROPERTY(EditAnywhere, meta=(ClampMin=0.f, EditCondition="MovementType != EMovementType::Linear", EditConditionHides))
	float BounceSpeed;

	FMovementValues(): MovementType()
	{
		Amplitude = 1.f;
		BounceSpeed = 1.f;
	}
};

UCLASS()
class OPENWORLD_API AContinuouslyMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AContinuouslyMovingActor();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	FVector GetUpdatedOffsetCoordinate(const float DeltaTime) const;

private:
	void DrawDebugHelper() const;
	float GetOffsetWithMovementType(EMovementType MovementType, float DeltaTime, float BounceSpeed) const;

	UPROPERTY(VisibleInstanceOnly)
	float RunningTime = 0.f;

	UPROPERTY(EditAnywhere, AdvancedDisplay)
	bool MoveX = false;
	UPROPERTY(EditAnywhere, AdvancedDisplay, meta=(EditCondition="MoveX", EditConditionHides))
	FMovementValues XValues;

	UPROPERTY(EditAnywhere, AdvancedDisplay)
	bool MoveY = false;
	UPROPERTY(EditAnywhere, AdvancedDisplay, meta=(EditCondition="MoveY", EditConditionHides))
	FMovementValues YValues;
	
	UPROPERTY(EditAnywhere, AdvancedDisplay)
	bool MoveZ = false;
	UPROPERTY(EditAnywhere, AdvancedDisplay, meta=(EditCondition="MoveZ", EditConditionHides))
	FMovementValues ZValues;
};
