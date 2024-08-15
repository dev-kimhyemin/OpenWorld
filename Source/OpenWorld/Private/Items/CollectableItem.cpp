
#include "Items/CollectableItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Characters/Echo.h"


ACollectableItem::ACollectableItem()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	SetRootComponent(StaticMeshComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->SetupAttachment(GetRootComponent());
}

void ACollectableItem::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ACollectableItem::OnSphereBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ACollectableItem::OnSphereEndOverlap);
}

void ACollectableItem::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!bItemCollected)
	{
		AddActorWorldOffset(FVector(0.f, 0.f, GetTransformedSin()));
	}
}

float ACollectableItem::GetTransformedSin() const
{
	return FMath::Sin(GetGameTimeSinceCreation() * 3.0f) * 0.3f;
}


void ACollectableItem::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AEcho* Echo = Cast<AEcho>(OtherActor))
	{
		Echo->SetOverlappingItem(this);
	}
}

void ACollectableItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(AEcho* Echo = Cast<AEcho>(OtherActor))
	{
		Echo->SetOverlappingItem(nullptr);
	}
}
