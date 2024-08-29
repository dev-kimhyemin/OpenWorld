
#include "UI/ItemSlot.h"
#include "UI/StoreItemDataAsset.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


void UItemSlot::SetSlotWithItemData(UStoreItemDataAsset* ItemData)
{
	CurrentItemData = ItemData;
	
	NameTextBlock->SetText(ItemData->ItemName.ToUpper());
	PriceTextBlock->SetText(FText::FromString(FString::FromInt(ItemData->Price)));
	ItemImage->SetBrushFromMaterial(ItemData->ItemMaterial);
	BackgroundImage->SetBrushTintColor(ItemData->BackgroundColor);
}

void UItemSlot::SetSlotNonInteractable() const
{
	NameTextBlock->SetText(FText::FromString("SOLD OUT"));
	PriceTextBlock->SetText(FText::FromString(""));
	ItemImage->SetBrushFromMaterial(nullptr);
	BackgroundImage->SetBrushTintColor(FColor(0.5f, 0.5f, 0.5f));
}

void UItemSlot::OnSlotClicked()
{
	if(ClickedDelegate.IsBound())
	{
		ClickedDelegate.Execute(this);
	}
}

int UItemSlot::GetItemPrice() const
{
	return CurrentItemData ? CurrentItemData->Price : 0;
}

