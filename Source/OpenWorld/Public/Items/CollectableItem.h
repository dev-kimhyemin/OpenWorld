
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectableItem.generated.h"

class USphereComponent;
class UBoxComponent;


UCLASS()
class OPENWORLD_API ACollectableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ACollectableItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComponent;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	float GetTransformedSin() const;
	
	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(BlueprintReadOnly)
	bool bItemCollected = false;
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;
};
