
#pragma once

#include "CoreMinimal.h"
#include "Items/CollectableItem.h"
#include "Weapon.generated.h"

class USoundBase;
class UBoxComponent;


UCLASS()
class OPENWORLD_API AWeapon : public ACollectableItem
{
	GENERATED_BODY()

public:
	AWeapon();
	void AttachMeshToSocket(USceneComponent* InParent, FName InSocketName) const;
	void Equip(USceneComponent* InParent, FName InSocketName);
	
	FORCEINLINE void SetBoxCollisionEnabled(const ECollisionEnabled::Type CollisionEnabled);
	
protected:
	virtual void BeginPlay() override;
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	USoundBase* EquipSound;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	UBoxComponent* HitBoxComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	USceneComponent* BoxTraceStart;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	USceneComponent* BoxTraceEnd;

	UPROPERTY()
	TArray<AActor*> IgnoreActors;
};
