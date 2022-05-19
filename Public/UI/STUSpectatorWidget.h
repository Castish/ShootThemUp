// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUSpectatorWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category= "UI")
	bool GetRespawnTime(int32& CountDownTime) const;
	
};
