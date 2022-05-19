// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/STUMenuPlayerController.h"

#include "STUGameInstance.h"

void ASTUMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

}