
#pragma once

#include "CoreMinimal.h"
#include "Items/CollectableItem.h"
#include "Weapon.generated.h"

class USoundBase;

UCLASS()
class OPENWORLD_API AWeapon : public ACollectableItem
{
	GENERATED_BODY()

public:
	void AttachMeshToSocket(USceneComponent* InParent, FName InSocketName) const;
	void Equip(USceneComponent* InParent, FName InSocketName);
	
protected:
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

private:
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	USoundBase* EquipSound;
};
