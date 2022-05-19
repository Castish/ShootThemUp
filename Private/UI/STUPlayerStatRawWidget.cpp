// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUPlayerStatRawWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void USTUPlayerStatRawWidget::SetPlayerName(const FText& Text)
{
	if (!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void USTUPlayerStatRawWidget::SetKills(const FText& Text)
{
	if (!KillsTextBlock) return;
	KillsTextBlock->SetText(Text);
}

void USTUPlayerStatRawWidget::SetDeaths(const FText& Text)
{
	if (!DeathsTextBlock) return;
	DeathsTextBlock->SetText(Text);
}

void USTUPlayerStatRawWidget::SetTeam(const FText& Text)
{
	if (!TeamTextBlock) return;
	TeamTextBlock->SetText(Text);
}

void USTUPlayerStatRawWidget::SetPlayerIndicatorVisibility(bool Visible)
{
	if (!PlayerIndicatorImage) return;
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
