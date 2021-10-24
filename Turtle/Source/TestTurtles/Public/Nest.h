// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turtle.h"
#include "Nest.generated.h"

USTRUCT()
struct FTurtleData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATurtle> Turtle;

	UPROPERTY(EditAnywhere)
	float Distance;

	UPROPERTY(EditAnywhere)
	bool Stay;

	UPROPERTY(EditAnywhere)
	bool MoveBack;
	//
	// UPROPERTY(EditAnywhere)
	// FTransform InitialTransform;
};

class AStartButton;
UCLASS()
class TESTTURTLES_API ANest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Button Target")
	AStartButton* StartButton;

	UPROPERTY(EditAnywhere)
	FTurtleData TurtleData;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnTurtle();
};


