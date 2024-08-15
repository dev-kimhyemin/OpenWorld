#pragma once

#include "Items/Weapons/Weapon.h"
#include "Characters/Echo.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


void AWeapon::AttachMeshToSocket(USceneComponent* InParent, const FName InSocketName) const
{
	const FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	StaticMeshComponent->AttachToComponent(InParent, TransformRules, InSocketName);
}

void AWeapon::Equip(USceneComponent* InParent, const FName InSocketName)
{
	bItemCollected = true;
	
	AttachMeshToSocket(InParent, InSocketName);

	if(SphereComponent)
	{
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if(EquipSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, EquipSound, GetActorLocation());
	}
}
	

void AWeapon::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if(AEcho* Echo = Cast<AEcho>(OtherActor))
	{
		Echo->SetOverlappingItem(this);
	}
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	
	if(AEcho* Echo = Cast<AEcho>(OtherActor))
	{
		Echo->SetOverlappingItem(nullptr);
	}
}
