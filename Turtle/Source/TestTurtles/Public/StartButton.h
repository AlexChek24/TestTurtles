// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Turtle.h"
#include "Engine/StaticMeshActor.h"
#include "StartButton.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnTarget)


UCLASS()
class TESTTURTLES_API AStartButton : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AStartButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FOnTarget OnTarget;
	
	
	UFUNCTION()
	void OnSelected(AActor* Target, FKey Mouseclick);
};
