
#pragma once

#include "CoreMinimal.h"

class UItemSlot;
DECLARE_DELEGATE_OneParam(SlotClickedDelegate, UItemSlot*)


class OPENWORLD_API ItemStoreAttributes
{
public:
	SlotClickedDelegate OnSlotClicked;

	void TriggerDelegate(UItemSlot* ClickedSlot) const
	{
		if(OnSlotClicked.IsBound())
		{
			OnSlotClicked.Execute(ClickedSlot);
		}
	}
};
