
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
	virtual void OnGetHit(const FVector& ImpactPoint) override;

protected:
	FName GetReactNameFromImpactPoint(const FVector& ImpactPoint) const;
	void PlayHitReactMontage(const FName& SectionName) const;

private:
	void PlayEffects(const FVector& ImpactPoint) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Enemy Properties")
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditAnywhere, Category = "Enemy Properties")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Enemy Properties")
	UParticleSystem* BloodParticle;
	
};
