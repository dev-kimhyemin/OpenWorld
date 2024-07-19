// Fill out your copyright notice in the Description page of Project Settings.


#include "Tools/DebugTool.h"
#include "Engine/Engine.h"

#define DEBUG_HELPER_LIFETIME 100.f

ADebugTool::ADebugTool()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADebugTool::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay called"));

	DrawDebugHelpers();
}

void ADebugTool::DrawDebugHelpers() const
{
	if(const UWorld* World = GetWorld())
	{
		const FVector Location = GetActorLocation();
		const FVector ForwardVector = GetActorForwardVector();
		const FVector UpVector = GetActorUpVector();
		const FVector LineEnd = Location + ForwardVector * 100;
		
		DrawDebugSphere(World, Location, 50.f, 30, FColor::Magenta, false, DEBUG_HELPER_LIFETIME);
		DrawDebugLine(World, Location, LineEnd, FColor:: Magenta, false, DEBUG_HELPER_LIFETIME, 0, 3);
		DrawDebugPoint(World, LineEnd, 15, FColor:: Cyan, false, DEBUG_HELPER_LIFETIME);
		DrawDebugCylinder(World, Location - ForwardVector * 10, Location + ForwardVector * 10, 55.f, 30, FColor::Yellow, false, DEBUG_HELPER_LIFETIME, 0, 1);
		DrawDebugCylinder(World, Location - UpVector * 10, Location + UpVector * 10, 55.f, 30, FColor::Yellow, false, DEBUG_HELPER_LIFETIME, 0, 1);
	}
}

void ADebugTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(GEngine)
	{
		const FString Name = GetName();
		const FString DeltaTimeString = FString::Printf(TEXT("Actor %s display log / DeltaTime: %f"), *Name, DeltaTime);
		
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, DeltaTimeString);
	}
}


