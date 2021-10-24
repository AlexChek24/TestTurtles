// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"

#include "Turtle.generated.h"

class UTimelineComponent;
UCLASS()
class TESTTURTLES_API ATurtle : public ACharacter
{
	GENERATED_BODY()

	
	
public:	
	// Sets default values for this actor's properties
	ATurtle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool Stay;
	bool MoveBack;
	float Distance;
	bool bImGoingUp = true;
	FTimerHandle TurtleTimerHandle;
	UTimelineComponent* ForwardTimeLine;
	UTimelineComponent* StayBackTimeLine;
	uint16 CallTrackerMove = 100;
	uint16 CallTrackerStayAndBack = 25;
	float StarPosition;

	UPROPERTY(EditAnywhere, Category = "Timeline");
	UCurveFloat* FForwardCurve;

	UPROPERTY(EditAnywhere, Category = "Timeline");
	UCurveFloat* FStayBackCurve;

	UPROPERTY(EditDefaultsOnly,Category = "Animation")
	UAnimMontage* AMIdle;

	UPROPERTY(EditDefaultsOnly,Category = "Animation")
	UAnimMontage* AMRun;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetTurtleData(float Distance_, bool Stay_,bool MoveBack_)
	{
		Stay = Stay_;
		MoveBack = MoveBack_;
		Distance = Distance_;
	};
	
	

	void MovingForwardEvent();
	void StayingEvent();
	void MovingBackEvent();

	FOnTimelineFloat ForwardInteruptFunc{};
	FOnTimelineEvent ForwardTimeLineFinished{};
	FOnTimelineFloat StayBackInteruptFunc{};
	FOnTimelineEvent StayBackTimeLineFinished{};
	UFUNCTION()
	void ForwardTimeLineReturn (float value);
	UFUNCTION()
    void StayBackTimeLineReturn (float value);


	UFUNCTION()
	void ForwardOnTimeLineFinished();
	UFUNCTION()
	void StayBackOnTimeLineFinished();
};
