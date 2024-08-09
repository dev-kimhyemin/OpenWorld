
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ContinuouslyMovingActor.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Linear			UMETA(DisplayName="Linear"),
	SinPingPong		UMETA(DisplayName="SinPingPong"),
	CosPingPong		UMETA(DisplayName="CosPingPong")
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

	FString ToString() const;

	FMovementValues()
	{
		MovementType = EMovementType::Linear;
		Amplitude = 1.f;
		BounceSpeed = 1.f;
	}
};

inline FString FMovementValues::ToString() const
{
	return FString::Printf(TEXT("Amplitude=%f BounceSpeed=%f"), Amplitude, BounceSpeed);
}

UCLASS()
class OPENWORLD_API AContinuouslyMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AContinuouslyMovingActor();
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable)
	FVector GetUpdatedOffsetCoordinate(const float DeltaTime) const;

	FRotator GetUpdatedRotatorCoordinate(const float DeltaTime) const;
	float GetUpdatedOffsetPoint(const FMovementValues MovementValues, const float DeltaTime) const;

private:
	float GetOffsetWithMovementType(EMovementType MovementType, float DeltaTime, float BounceSpeed) const;

	UPROPERTY(VisibleInstanceOnly)
	float RunningTime = 0.f;

	UPROPERTY(EditAnywhere, AdvancedDisplay)
	bool MoveX = false;
	UPROPERTY(EditAnywhere, AdvancedDisplay, meta=(EditCondition="MoveX", EditConditionHides))
	FMovementValues XMovementValues;

	UPROPERTY(EditAnywhere, AdvancedDisplay)
	bool MoveY = false;
	UPROPERTY(EditAnywhere, AdvancedDisplay, meta=(EditCondition="MoveY", EditConditionHides))
	FMovementValues YMovementValues;
	
	UPROPERTY(EditAnywhere, AdvancedDisplay)
	bool MoveZ = false;
	UPROPERTY(EditAnywhere, AdvancedDisplay, meta=(EditCondition="MoveZ", EditConditionHides))
	FMovementValues ZMovementValues;

	UPROPERTY(EditAnywhere, AdvancedDisplay)
	bool RotateX = false;
	UPROPERTY(EditAnywhere, AdvancedDisplay, meta=(EditCondition="RotateX", EditConditionHides))
	FMovementValues XRotationValues;

	UPROPERTY(EditAnywhere, AdvancedDisplay)
	bool RotateY = false;
	UPROPERTY(EditAnywhere, AdvancedDisplay, meta=(EditCondition="RotateY", EditConditionHides))
	FMovementValues YRotationValues;

	UPROPERTY(EditAnywhere, AdvancedDisplay)
	bool RotateZ = false;
	UPROPERTY(EditAnywhere, AdvancedDisplay, meta=(EditCondition="RotateZ", EditConditionHides))
	FMovementValues ZRotationValues;
};

