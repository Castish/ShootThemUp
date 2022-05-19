// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "STUGameModeBase.h"
#include "Chaos/ChaosPerfTest.h"
#include "Player/STUPlayerController.h"
#include "UI/STUStatisticsWidget.h"


ASTUGameHUD::ASTUGameHUD()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASTUGameHUD::DrawHUD()
{
	Super::DrawHUD();
	//DrawCrossHair();
}

void ASTUGameHUD::BeginPlay()
{
	Super::BeginPlay();


	GameWidgets.Add(ESTUMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(ESTUMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(ESTUMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));
	CreateStatisticsWidget();
	for (auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GetWorld())
	{
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ASTUGameHUD::OnMatchStateChanged);
		}
		const auto Controller = Cast<ASTUPlayerController>(GetOwningPawn()->Controller);
		Controller->TabPressed.AddUObject(this, &ASTUGameHUD::OnTabPressed);
	}
}

void ASTUGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	StatisticsWidget->UpdatePlayersStat();
}

void ASTUGameHUD::OnTabPressed(bool Tab)
{
	if (Tab)
	{
		StatisticsWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else if (!Tab)
	{
		StatisticsWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ASTUGameHUD::CreateStatisticsWidget()
{
	StatisticsWidget = CreateWidget<USTUStatisticsWidget>(GetWorld(), PlayerStatisticsClass);
	if (!StatisticsWidget) return;
	StatisticsWidget->AddToViewport();
	StatisticsWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ASTUGameHUD::DrawCrossHair()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;
	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}

void ASTUGameHUD::OnMatchStateChanged(ESTUMatchState State)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
	UE_LOG(LogTemp, Display, TEXT("Match State Changed: %s"), *UEnum::GetValueAsString(State))
}
