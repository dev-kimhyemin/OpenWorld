#pragma once

#include "Items/Weapons/Weapon.h"
#include "Characters/Echo.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Interfaces/HitReceiver.h"


AWeapon::AWeapon()
{
	HitBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBoxComponent->SetupAttachment(GetRootComponent());
	HitBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("BoxTraceStart"));
	BoxTraceStart->SetupAttachment(GetRootComponent());
	
	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("BoxTraceEnd"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	HitBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxBeginOverlap);
}

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

void AWeapon::SetBoxCollisionEnabled(const ECollisionEnabled::Type CollisionEnabled)
{
	if(HitBoxComponent)
	{
		HitBoxComponent->SetCollisionEnabled(CollisionEnabled);
	}

	if(CollisionEnabled == ECollisionEnabled::NoCollision)
	{
		IgnoreActors.Empty();
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

void AWeapon::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector StartLocation = BoxTraceStart->GetComponentLocation();
	const FVector EndLocation = BoxTraceEnd->GetComponentLocation();
	const FVector HalfSize = FVector::One() * 5.0f;

	TArray<AActor*> ActorsToIgnore {this};
	for (AActor* IgnoreActor : IgnoreActors)
	{
		ActorsToIgnore.AddUnique(IgnoreActor);
	}
	
	FHitResult HitResult;

	UKismetSystemLibrary::BoxTraceSingle(
		this,
		StartLocation,
		EndLocation,
		HalfSize,
		BoxTraceStart->GetComponentRotation(),
		TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		true
	);

	if(AActor* HitActor = HitResult.GetActor())
	{
		if(IHitReceiver* HitReceiver = Cast<IHitReceiver>(HitActor))
		{
			HitReceiver->OnGetHit(HitResult.ImpactPoint);
		}

		IgnoreActors.AddUnique(HitActor);
	}
}
