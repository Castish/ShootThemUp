// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUGameOverWidget.h"
#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"
#include "UI/STUPlayerStatRawWidget.h"
#include "Components/VerticalBox.h"
#include "STUUtils.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"

void USTUGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GetWorld())
	{
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);
		}
	}

	if (GoToMainMenuButton)
	{
		GoToMainMenuButton->OnClicked.AddDynamic(this, &USTUGameOverWidget::OnToMainMenuButton);
	}

	if (ResetLevelButton)
	{
		ResetLevelButton->OnClicked.AddDynamic(this, &USTUGameOverWidget::OnResetLevel);
	}
}

void USTUGameOverWidget::OnMatchStateChanged(ESTUMatchState State)
{
	if (State == ESTUMatchState::GameOver)
	{
		UpdatePlayersStat();
	}
}

void USTUGameOverWidget::UpdatePlayersStat()
{
	if (!GetWorld() || !PlayerStatBox) return;

	PlayerStatBox->ClearChildren();

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		const auto PlayerStateRowWidget = CreateWidget<USTUPlayerStatRawWidget>(GetWorld(), PlayerStateRowWidgetClass);
		if (!PlayerStateRowWidget) continue;

		PlayerStateRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStateRowWidget->SetKills(STUUtils::TextFromInt(PlayerState->GetKillsNum()));
		PlayerStateRowWidget->SetDeaths(STUUtils::TextFromInt(PlayerState->GetDeathsNum()));
		PlayerStateRowWidget->SetTeam(STUUtils::TextFromInt(PlayerState->GetTeamID()));
		PlayerStateRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

		PlayerStatBox->AddChild(PlayerStateRowWidget);
	}
}

void USTUGameOverWidget::OnResetLevel()
{
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);

	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}

void USTUGameOverWidget::OnToMainMenuButton()
{
	if (!GetWorld()) return;

	const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
	if (!STUGameInstance) return;

	if (STUGameInstance->GetMainMenuName().IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT ("Level Name of Main Menu is NONE"));
		return;
	}

	UGameplayStatics::OpenLevel(this, STUGameInstance->GetMainMenuName());
}
