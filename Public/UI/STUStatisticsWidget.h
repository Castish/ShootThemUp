// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUStatisticsWidget.generated.h"


class UVerticalBox;
class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUStatisticsWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//void ShowStatistics();
	//void HideStatistics();
	void UpdatePlayersStat();
protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> PlayerStateRowWidgetClass;
	
	virtual void NativeOnInitialized() override;
private:

	

	
};
