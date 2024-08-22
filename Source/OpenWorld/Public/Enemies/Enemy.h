
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitReceiver.h"
#include "Enemy.generated.h"

class UAnimMontage;


UCLASS()
class OPENWORLD_API AEnemy : public ACharacter, public IHitReceiver
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnGetHit(const FVector& ImpactPoint) override;

protected:
	virtual void BeginPlay() override;
	FName GetReactNameFromImpactPoint(const FVector& ImpactPoint) const;
	void PlayHitReactMontage(const FName& SectionName) const;

private:
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* HitReactMontage;
};
