// Fill out your copyright notice in the Description page of Project Settings.


#include "TurtleGameMode.h"
#include "TestTurtles/Public/TurtleController.h"
ATurtleGameMode::ATurtleGameMode()
{
	PlayerControllerClass = ATurtleController::StaticClass();
}
