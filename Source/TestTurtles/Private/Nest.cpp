// Fill out your copyright notice in the Description page of Project Settings.


#include "Nest.h"

#include "StartButton.h"

// Sets default values
ANest::ANest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANest::BeginPlay()
{
	Super::BeginPlay();
	StartButton->OnTarget.AddUObject(this,&ANest::SpawnTurtle);
}

// Called every frame
void ANest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANest::SpawnTurtle()
{

	UWorld* World = GetWorld();
	if(World)
	{
		FTransform CurrentActorTransform =  GetActorTransform();
		CurrentActorTransform.SetLocation(FVector(GetActorLocation().X+50,GetActorLocation().Y,20));
		ATurtle* Turtle =  World->SpawnActorDeferred<ATurtle>(TurtleData.Turtle,CurrentActorTransform);
		if(Turtle)
		{
			Turtle->SetTurtleData(TurtleData.Distance,TurtleData.Stay,TurtleData.MoveBack);
			Turtle->FinishSpawning(CurrentActorTransform);
		}	
	}
}