
#include "UI/ItemStore.h"
#include "UI/ItemSlot.h"
#include "UI/StoreItemDataAsset.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"


void UItemStore::StoreInitialSetting(UPanelWidget* PanelWidget)
{
	InitializeItemDataAssets();
	UpdateBankBalanceTextBlock();

	SlotClickedDelegate Delegate;
	Delegate.BindUObject(this, &UItemStore::OnSlotClicked);
	
	for(UWidget* Widget : PanelWidget->GetAllChildren())
	{
		if(UItemSlot* ItemSlot = Cast<UItemSlot>(Widget))
		{
			ItemSlots.AddUnique(ItemSlot);
			ItemSlot->InitializeSlotClickedDelegate(Delegate);
			SetSlot(ItemSlot);
		}
	}
}

void UItemStore::SetSlot(UItemSlot* ItemSlot)
{
	if(UStoreItemDataAsset* TargetItemData = GetAvailableItemData())
	{
		ItemSlot->SetSlotWithItemData(TargetItemData);
	}
	else
	{
		ItemSlot->SetSlotNonInteractable();
	}
}

UStoreItemDataAsset* UItemStore::GetAvailableItemData()
{
	if(SearchItemCount == StoreItemDataAssets.Num())
	{
		return nullptr;
	}
	
	const int InitialIndex = FMath::RandRange(0, StoreItemDataAssets.Num() - 1);
	int CurrentIndex = InitialIndex;

	do
	{
		if(!StoreItemDataAssets[CurrentIndex]->bIsShown)
		{
			StoreItemDataAssets[CurrentIndex]->bIsShown = true;
			++SearchItemCount;
			return StoreItemDataAssets[CurrentIndex];
		}

		CurrentIndex = (CurrentIndex + 1) % StoreItemDataAssets.Num();
	}
	while (CurrentIndex != InitialIndex);

	return nullptr;
}

void UItemStore::OnSlotClicked(UItemSlot* ClickedSlot)
{
	if(BankBalance > ClickedSlot->GetItemPrice())
	{
		BankBalance -= ClickedSlot->GetItemPrice();
		UpdateBankBalanceTextBlock();
		
		SetSlot(ClickedSlot);
	}
}

void UItemStore::InitializeItemDataAssets()
{
	for (UStoreItemDataAsset* ItemDataAsset : StoreItemDataAssets)
	{
		ItemDataAsset->bIsShown = false;
	}
}

void UItemStore::UpdateBankBalanceTextBlock() const
{
	if(BankBalanceTextBlock)
	{
		BankBalanceTextBlock->SetText(FText::FromString(FString::FromInt(BankBalance)));
	}
}




