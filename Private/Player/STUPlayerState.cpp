// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/STUPlayerState.h"

void ASTUPlayerState::LogInfo()
{
	UE_LOG(LogTemp, Display, TEXT("Team ID: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathsNum);
}
