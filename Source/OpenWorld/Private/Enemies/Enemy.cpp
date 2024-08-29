
#include "Enemies/Enemy.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}

void AEnemy::OnGetHit(const FVector& ImpactPoint)
{
	// DrawDebugSphere(GetWorld(), ImpactPoint, 15.0f, 25, FColor::Orange, false, 3.0f, 0, 0.5f);
	
	PlayHitReactMontage(GetReactNameFromImpactPoint(ImpactPoint));
	PlayEffects(ImpactPoint);
}

void AEnemy::PlayEffects(const FVector& ImpactPoint) const
{
	if(HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, ImpactPoint);
	}

	if(BloodParticle)
	{
		const FRotator BloodRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ImpactPoint);

		// Draw debug arrow
		// const FVector Direction = BloodRotation.Vector();
		// const FVector EndLocation = GetActorLocation() + Direction * 100.f;
		// UKismetSystemLibrary::DrawDebugArrow(this, ImpactPoint, EndLocation, 10.f, FColor::Blue, 3.f, 1.f);
		
		UGameplayStatics::SpawnEmitterAtLocation(this, BloodParticle, ImpactPoint, BloodRotation);
	}
}

FName AEnemy::GetReactNameFromImpactPoint(const FVector& ImpactPoint) const
{
	const FVector Forward = GetActorForwardVector();
	const FVector ArrangedImpactPoint(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	const FVector ToHit = (ArrangedImpactPoint - GetActorLocation()).GetSafeNormal();

	// Forward * ToHit = |Forward||ToHit| * cos(theta)
	// Both two vectors are normalized, so Forward * ToHit = cos(theta)
	const double Cos = FVector::DotProduct(Forward, ToHit);
	double Theta = FMath::RadiansToDegrees(FMath::Acos(Cos));

	// If CrossProduct points down, Theta should be negative
	const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit); 
	if(CrossProduct.Z < 0)
	{
		Theta *= -1.f;
	}

	FName ReactName("FromBack");

	if(Theta >= -45.f && Theta < 45.f)
	{
		ReactName = FName("FromFront");
	}
	else if(Theta >= -135.f && Theta < -45.f)
	{
		ReactName = FName("FromRight");
	}
	else if(Theta >= 45.f && Theta < 135.f)
	{
		ReactName = FName("FromLeft");
	}
	
	// UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + Forward * 150.f, 1.f, FColor::Red, 3.f, 0.5f);
	// UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + ToHit * 150.f, 1.f, FColor::Green, 3.f, 0.5f);
	// UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + CrossProduct * 150.f, 1.f, FColor::Blue, 3.f, 0.5f);

	return ReactName;
}

void AEnemy::PlayHitReactMontage(const FName& SectionName) const
{
	if(UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		AnimInstance->Montage_Play(HitReactMontage);
		AnimInstance->Montage_JumpToSection(SectionName, HitReactMontage);
	}
}


