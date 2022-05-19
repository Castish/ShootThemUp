// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/STULevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void USTULevelItemWidget::SetLevelData(const FLevelData& Data)
{
	LevelData = Data;
	if(LevelNameTextBlock)
	{
		LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
	}

	if(LevelImage)
	{
		LevelImage->SetBrushFromTexture(Data.LevelThub);
	}
}

void USTULevelItemWidget::SetSelected(bool InSelected)
{
	if(FrameImage)
	{
		FrameImage->SetVisibility((IsSelected() ? ESlateVisibility::Visible : ESlateVisibility::Hidden));
	}
}

void USTULevelItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(LevelSelectButton)
	{
		LevelSelectButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::OnLevelItemClicked);
	}
}

void USTULevelItemWidget::OnLevelItemClicked()
{
	OnLevelSelected.Broadcast(LevelData);
}
