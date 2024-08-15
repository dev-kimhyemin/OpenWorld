#pragma once

UENUM(BlueprintType)
enum class ECharacterEquipmentState : uint8
{
	Unequipped	UMETA(DisplayName = "Unequipped"),
	OneHanded	UMETA(DisplayName = "OneHanded"),
};

UENUM(BlueprintType)
enum class ECharacterActionState : uint8
{
	Unoccupied	UMETA(DisplayName = "Unoccupied"),
	Attacking	UMETA(DisplayName = "Attacking"),
	Arming		UMETA(DisplayName = "Arming"),
};
