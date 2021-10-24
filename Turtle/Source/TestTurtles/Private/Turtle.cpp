// Fill out your copyright notice in the Description page of Project Settings.


#include "Turtle.h"

#include "Chaos/AABB.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "FloatingPawnMovement.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogKek, All, All);
// Sets default values
ATurtle::ATurtle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ForwardTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("ForwardTimeline"));
	StayBackTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("StayBackTimeline"));
	
	ForwardInteruptFunc.BindUFunction(this,FName("ForwardTimeLineReturn"));
	StayBackInteruptFunc.BindUFunction(this,FName("StayBackTimeLineReturn"));
	ForwardTimeLineFinished.BindUFunction(this, FName("ForwardOnTimeLineFinished"));
	StayBackTimeLineFinished.BindUFunction(this, FName("StayBackOnTimeLineFinished"));
	StarPosition = GetActorLocation().X;
}

// Called when the game starts or when spawned
void ATurtle::BeginPlay()
{
	Super::BeginPlay();
	//GetWorld()->GetTimerManager().SetTimer(TurtleTimerHandle,this,&ATurtle::MovingForwardEvent,0.01f,true);
	if(FForwardCurve && FStayBackCurve)
	{
		ForwardTimeLine->AddInterpFloat(FForwardCurve,ForwardInteruptFunc,FName("Alpha"));
		ForwardTimeLine->SetTimelineFinishedFunc(ForwardTimeLineFinished);
		ForwardTimeLine ->SetLooping(false);

		StayBackTimeLine->AddInterpFloat(FStayBackCurve,StayBackInteruptFunc,FName("Beta"));
		StayBackTimeLine->SetTimelineFinishedFunc(StayBackTimeLineFinished);
		StayBackTimeLine ->SetLooping(false);
		PlayAnimMontage(AMRun);
		ForwardTimeLine->Play();
	}
}

// Called every frame
void ATurtle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurtle::MovingForwardEvent()
{
	if(GetActorLocation().X < StarPosition+Distance)
	{
		CallTrackerMove--;
		if(CallTrackerMove == 0)
		{
			if(!Stay && !MoveBack)
			{
				CallTrackerMove = 100;
			} else if(Stay)
			{
				GetWorldTimerManager().SetTimer(TurtleTimerHandle,this,&ATurtle::StayingEvent,0.02f,true);
				CallTrackerMove = 100;
			}else
			{
				FRotator RotateBack =  GetActorRotation();
				RotateBack.Yaw +=180;
				SetActorRotation(RotateBack);
				GetWorldTimerManager().SetTimer(TurtleTimerHandle,this,&ATurtle::MovingBackEvent,0.02f,true);
				CallTrackerMove = 100;
			}
		}
		if(CallTrackerMove>0)
		{
			FVector Location =  GetActorLocation()+GetActorForwardVector()*100*GetWorldTimerManager().GetTimerRate((TurtleTimerHandle));
			SetActorLocation(Location);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TurtleTimerHandle);
	}
}

void ATurtle::StayingEvent()
{
	CallTrackerStayAndBack--;
	if(CallTrackerStayAndBack == 0)
	{
		GetWorld()->GetTimerManager().SetTimer(TurtleTimerHandle,this,&ATurtle::MovingForwardEvent,0.01f,true);
		CallTrackerStayAndBack = 25;
	}
}

void ATurtle::MovingBackEvent()
{
	CallTrackerStayAndBack--;
	if(CallTrackerMove>0)
	{
		FVector Location =  GetActorLocation()+GetActorForwardVector()*100*GetWorldTimerManager().GetTimerRate((TurtleTimerHandle));
		SetActorLocation(Location);
	}
	if(CallTrackerStayAndBack == 0)
	{
		FRotator RotateBack =  GetActorRotation();
		RotateBack.Yaw +=180;
		SetActorRotation(RotateBack);
		GetWorld()->GetTimerManager().SetTimer(TurtleTimerHandle,this,&ATurtle::MovingForwardEvent,0.01f,true);
		CallTrackerStayAndBack = 25;
	}
}

void ATurtle::ForwardTimeLineReturn(float value)
{
	if(ForwardTimeLine->GetPlaybackPosition() <1.0f && GetActorLocation().X < StarPosition+Distance)
	{
		SetActorLocation(GetActorLocation()+GetActorForwardVector()*2);
		UE_LOG(LogKek,Warning,TEXT("GetPlaybackPosition Forward Return = % f"),ForwardTimeLine->GetPlaybackPosition());
	}else if((MoveBack || Stay)  && GetActorLocation().X < StarPosition+Distance )
	{
		StayBackTimeLine->Play();
	}else
	{
		StopAnimMontage();
	}
}

void ATurtle::StayBackTimeLineReturn(float value)
{
	if(StayBackTimeLine->GetPlaybackPosition() <0.5f )
	{
		UE_LOG(LogKek,Warning,TEXT("GetPlaybackPosition StayBackReturn = %f"),StayBackTimeLine->GetPlaybackPosition());
		if(MoveBack)
		{
			SetActorLocation(GetActorLocation()+GetActorForwardVector()*(2));
		}
	}
}

void ATurtle::StayBackOnTimeLineFinished()
{
	UE_LOG(LogKek,Warning,TEXT("GetPlaybackPosition ForwardFinished = %f"),StayBackTimeLine->GetPlaybackPosition());
	StayBackTimeLine->SetPlaybackPosition(0.0,false,false);
	if(MoveBack){
		FRotator RotateBack =  GetActorRotation();
		RotateBack.Yaw +=180;
		SetActorRotation(RotateBack);
	}
	if(GetActorLocation().X < StarPosition+Distance)
	{
		PlayAnimMontage(AMRun);
		ForwardTimeLine->Play();
	}
}

void ATurtle::ForwardOnTimeLineFinished()
{
	if(GetActorLocation().X < StarPosition+Distance && ForwardTimeLine->GetPlaybackPosition() == ForwardTimeLine->GetTimelineLength())
	{
		UE_LOG(LogKek,Warning,TEXT("GetPlaybackPosition ForwardFinished = %f"),ForwardTimeLine->GetPlaybackPosition());
		ForwardTimeLine->SetPlaybackPosition(0.0,false,false);
		if(!MoveBack && !Stay)
			ForwardTimeLine->Play();
		if(MoveBack){
			FRotator RotateBack =  GetActorRotation();
			RotateBack.Yaw +=180;
			SetActorRotation(RotateBack);
		}
		if(MoveBack || Stay){
			if(Stay)
				PlayAnimMontage(AMIdle);
			StayBackTimeLine->Play();
		}
		else{
			PlayAnimMontage(AMRun);
		    ForwardTimeLine->Play();
		}
	}else
	{
		StopAnimMontage();
	}
}






