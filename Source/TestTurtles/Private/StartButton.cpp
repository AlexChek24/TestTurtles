// Fill out your copyright notice in the Description page of Project Settings.


#include "StartButton.h"

// Sets default values
AStartButton::AStartButton()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OnClicked.AddUniqueDynamic(this,&AStartButton::OnSelected);
}

// Called when the game starts or when spawned
void AStartButton::BeginPlay()
{
	Super::BeginPlay();		
}

// Called every frame
void AStartButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input


void AStartButton::OnSelected(AActor* Target, FKey Mouseclick)
{

	OnTarget.Broadcast();
	OnClicked.Clear();
}

