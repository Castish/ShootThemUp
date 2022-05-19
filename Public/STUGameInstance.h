// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUCoreTypes.h"
#include "STUGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	FName GetMainMenuName() const {return  MainMenuName;}
	FLevelData GetStartupLevelName() const {return  StartupLevel;}
	
	void SetStartupLevel(const FLevelData& Data) {StartupLevel = Data;}
	
	TArray<FLevelData> GetLevelsData() {return LevelsData;}
protected:
	UPROPERTY(EditDefaultsOnly, Category="Game")
	TArray<FLevelData> LevelsData;
	
	UPROPERTY(EditDefaultsOnly, Category="Game")
	FName MainMenuName = NAME_None;

private:
	FLevelData StartupLevel;
};
