// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DebugTool.generated.h"

UCLASS()
class OPENWORLD_API ADebugTool : public AActor
{
	GENERATED_BODY()
	
public:	
	ADebugTool();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	void DrawDebugHelpers() const;
	void ShowFrameRate(float DeltaTime) const;
};
