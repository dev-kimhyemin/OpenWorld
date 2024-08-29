
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemStore.generated.h"

class UTextBlock;
class UItemSlot;
class UStoreItemDataAsset;

DECLARE_DELEGATE_OneParam(SlotClickedDelegate, UItemSlot*);


UCLASS()
class OPENWORLD_API UItemStore : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TArray<UItemSlot*> ItemSlots;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* BankBalanceTextBlock;

private:
	UFUNCTION(BlueprintCallable)
	void StoreInitialSetting(UPanelWidget* PanelWidget);

	void SetSlot(UItemSlot* ItemSlot);
	void OnSlotClicked(UItemSlot* ClickedSlot);
	void InitializeItemDataAssets();
	void UpdateBankBalanceTextBlock() const;

	UStoreItemDataAsset* GetAvailableItemData();
	
	UPROPERTY(EditAnywhere)
	TArray<UStoreItemDataAsset*> StoreItemDataAssets;

	int SearchItemCount = 0;
	int BankBalance = 20000;
};
