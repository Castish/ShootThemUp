// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"
#include "STUGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USTUPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this,&USTUPauseWidget::OnClearPause);
		GoToMainMenuButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnToMainMenuButton);
	}
}

void USTUPauseWidget::OnClearPause()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}

void USTUPauseWidget::OnToMainMenuButton()
{
	if(!GetWorld()) return;

	const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
	if (!STUGameInstance) return;

	if (STUGameInstance->GetMainMenuName().IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT ("Level Name of Main Menu is NONE"));
		return;
	}
	
	UGameplayStatics::OpenLevel(this, STUGameInstance->GetMainMenuName());
}
