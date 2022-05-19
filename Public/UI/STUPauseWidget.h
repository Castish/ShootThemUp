// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "STUPauseWidget.generated.h"

class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUPauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;

	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton* GoToMainMenuButton;
	
	
private:
	UFUNCTION()
	void OnClearPause();
	UFUNCTION()
	void OnToMainMenuButton();
};
