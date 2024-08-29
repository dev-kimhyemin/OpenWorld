
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StoreItemDataAsset.generated.h"


UCLASS()
class OPENWORLD_API UStoreItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText ItemName;

	UPROPERTY(EditAnywhere)
	UMaterial* ItemMaterial;

	UPROPERTY(EditAnywhere)
	FColor BackgroundColor;

	UPROPERTY(EditAnywhere)
	int Price;

	bool bIsShown;
};
