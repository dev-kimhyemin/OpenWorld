
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HitReceiver.generated.h"


UINTERFACE(MinimalAPI)
class UHitReceiver : public UInterface
{
	GENERATED_BODY()
};


class OPENWORLD_API IHitReceiver
{
	GENERATED_BODY()

public:
	virtual void OnGetHit(const FVector& ImpactPoint) = 0;
};
