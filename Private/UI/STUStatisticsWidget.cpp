// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUStatisticsWidget.h"

#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"
#include "UI/STUPlayerStatRawWidget.h"
#include "Components/VerticalBox.h"
#include "STUUtils.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"



void USTUStatisticsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}



void USTUStatisticsWidget::UpdatePlayersStat()
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

