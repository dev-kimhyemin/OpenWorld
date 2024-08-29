
#pragma once

#include "CoreMinimal.h"
#include "UI/ItemStoreAttributes.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlot.generated.h"

class UImage;
class UTextBlock;
class UStoreItemDataAsset;


UCLASS()
class OPENWORLD_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetSlotWithItemData(UStoreItemDataAsset* ItemData);
	void SetSlotNonInteractable() const;

	SlotClickedDelegate ClickedDelegate;
	
	void InitializeSlotClickedDelegate(const SlotClickedDelegate& InDelegate)
	{
		ClickedDelegate = InDelegate;
	}

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* NameTextBlock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* PriceTextBlock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UImage* BackgroundImage;

	UFUNCTION(BlueprintCallable)
	void OnSlotClicked();

private:
	UPROPERTY()
	UStoreItemDataAsset* CurrentItemData;

public:
	int GetItemPrice() const;
};
