// Fill out your copyright notice in the Description page of Project Settings.


#include "STUGameModeBase.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUGameHUD.h"
#include "Player/STUPlayerState.h"
#include "Components/STURespawnComponent.h"
#include "EngineUtils.h"

#include "STUGameInstance.h"
#include "Containers/UnrealString.h"
#include "Engine/PlayerStartPIE.h"


constexpr static int32 MinRoundTimeForRespawn = 10;

ASTUGameModeBase::ASTUGameModeBase()
{
	DefaultPawnClass = ASTUBaseCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
	PlayerStateClass = ASTUPlayerState::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
	
	Super::StartPlay();
	SpawnBots();


	CurrentRound = 1;
	StartRound();
	SetMatchState(ESTUMatchState::InProgress);
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

AActor* ASTUGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	CreateTeamsInfo();
	// Choose a player start
	// const auto GameState = GetWorld()->GetAuthGameMode()->GameState;
	const auto PlayerState = Cast<ASTUPlayerState>(Player->PlayerState);
	const auto TeamID = PlayerState->GetTeamID();
	UE_LOG(LogTemp, Error, TEXT("TeamID is a %i"), TeamID);
	FName Tag;
	if (TeamID == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("FName Tag == 1"));
		Tag = "One";
	}
	else if (TeamID == 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("FName Tag == 2"));
		Tag = "two";
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TeamID is nullptr"));
	}
	//APlayerStart* FoundPlayerStart = Cast<APlayerStart>(FindPlayerStart_Implementation(Player,Tag));
	APlayerStart* FoundPlayerStart = nullptr;
	UClass* PawnClass = GetDefaultPawnClassForController_Implementation(Player);
	APawn* PawnToFit = PawnClass ? PawnClass->GetDefaultObject<APawn>() : nullptr;
	TArray<APlayerStart*> UnOccupiedStartPointsOne;
	TArray<APlayerStart*> OccupiedStartPointsOne;
	TArray<APlayerStart*> UnOccupiedStartPointsTwo;
	TArray<APlayerStart*> OccupiedStartPointsTwo;
	UWorld* World = GetWorld();
	//	FName One = "One";
	//FName Two = "two";

	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		APlayerStart* PlayerStart = *It;

		if (PlayerStart->IsA<APlayerStartPIE>())
		{
			// Always prefer the first "Play from Here" PlayerStart, if we find one while in PIE mode
			UE_LOG(LogTemp, Warning, TEXT("PlayerStartPIE"));
			FoundPlayerStart = PlayerStart;
			break;
		}
		else if (PlayerStart->PlayerStartTag == Tag && TeamID == 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Tag is One"));
			FVector ActorLocation = PlayerStart->GetActorLocation();
			const FRotator ActorRotation = PlayerStart->GetActorRotation();
			if (!World->EncroachingBlockingGeometry(PawnToFit, ActorLocation, ActorRotation))
			{
				UnOccupiedStartPointsOne.Add(PlayerStart);
			}
			else if (World->FindTeleportSpot(PawnToFit, ActorLocation, ActorRotation))
			{
				OccupiedStartPointsOne.Add(PlayerStart);
			}
		}
		else if (PlayerStart->PlayerStartTag == Tag && TeamID == 2)
		{
			UE_LOG(LogTemp, Warning, TEXT("Tag is two"));
			FVector ActorLocation = PlayerStart->GetActorLocation();
			const FRotator ActorRotation = PlayerStart->GetActorRotation();
			if (!World->EncroachingBlockingGeometry(PawnToFit, ActorLocation, ActorRotation))
			{
				UnOccupiedStartPointsTwo.Add(PlayerStart);
			}
			else if (World->FindTeleportSpot(PawnToFit, ActorLocation, ActorRotation))
			{
				OccupiedStartPointsTwo.Add(PlayerStart);
			}
		}
	}
	if (FoundPlayerStart == nullptr && TeamID == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("FoundPlayerStart is nullptr"));
		if (UnOccupiedStartPointsOne.Num() > 0)
		{
			FoundPlayerStart = UnOccupiedStartPointsOne[FMath::RandRange(0, UnOccupiedStartPointsOne.Num() - 1)];
		}
		else if (OccupiedStartPointsOne.Num() > 0)
		{
			FoundPlayerStart = OccupiedStartPointsOne[FMath::RandRange(0, UnOccupiedStartPointsOne.Num() - 1)];
		}
	}
	else if (FoundPlayerStart == nullptr && TeamID == 2)
	{
		if (UnOccupiedStartPointsTwo.Num() > 0)
		{
			FoundPlayerStart = UnOccupiedStartPointsTwo[FMath::RandRange(0, UnOccupiedStartPointsTwo.Num() - 1)];
		}
		else if (OccupiedStartPointsOne.Num() > 0)
		{
			FoundPlayerStart = OccupiedStartPointsTwo[FMath::RandRange(0, UnOccupiedStartPointsTwo.Num() - 1)];
		}
	}
	return FoundPlayerStart;
}


AActor* ASTUGameModeBase::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	const auto PlayerState = Cast<ASTUPlayerState>(Player->PlayerState);
	//FString TeamTag;
	//TeamTag.AppendInt(PlayerState->GetTeamID());
	FName IncomingPlayerStartTag;
	if (PlayerState->GetTeamID() == 1)
	{
		UE_LOG(LogTemp, Display, TEXT("Team 1"))
		IncomingPlayerStartTag = "One";
	}
	else if (PlayerState->GetTeamID() == 2)
	{
		UE_LOG(LogTemp, Display, TEXT("Team 2"))
		IncomingPlayerStartTag = "two";
	}

	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* Start = *It;

		if (Start && Start->PlayerStartTag == IncomingPlayerStartTag)
		{
			return Start;
		}
	}

	return Super::FindPlayerStart_Implementation(Player, IncomingName);
}

bool ASTUGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
	if (PauseSet)
	{
		SetMatchState(ESTUMatchState::Pause);
	}
	return PauseSet;
}

bool ASTUGameModeBase::ClearPause()
{
	const auto PauseCleared = Super::ClearPause();
	if (PauseCleared)
	{
		SetMatchState(ESTUMatchState::InProgress);
	}
	
	return PauseCleared;
}


void ASTUGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState =
		KillerController ? Cast<ASTUPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState =
		VictimController ? Cast<ASTUPlayerState>(VictimController->PlayerState) : nullptr;

	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}
	if (VictimController)
	{
		VictimPlayerState->AddDeath();
	}

	StartRespawn(VictimController);
}

void ASTUGameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
}

void ASTUGameModeBase::StartRespawn(AController* Controller)
{
	const auto RespawnAvailable = RoundCountDown > MinRoundTimeForRespawn + GameData.RespawnTime;
	if (!RespawnAvailable) return;

	const auto RespawnComponent = STUUtils::GetSTUPlayerComponent<USTURespawnComponent>(Controller);
	if (!RespawnComponent) return;

	RespawnComponent->Respawn(GameData.RespawnTime);
}

void ASTUGameModeBase::GameOver()
{
	UE_LOG(LogTemp, Display, TEXT ("============== GAME OVER ==============="))
	LogPlayerInfo();

	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}
	SetMatchState(ESTUMatchState::GameOver);
}

void ASTUGameModeBase::SetMatchState(ESTUMatchState State)
{
	if (MatchState == State) return;

	MatchState = State;
	OnMatchStateChanged.Broadcast(MatchState);
}

void ASTUGameModeBase::LogPlayerInfo()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->LogInfo();
	}
}

void ASTUGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto STUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(STUAIController);
	}
}

void ASTUGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundsTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTUGameModeBase::GameTimerUpdate, 1.0f, true);
}

void ASTUGameModeBase::GameTimerUpdate()
{
	//	UE_LOG(LogTemp, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum)


	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			GameOver();
		}
	}
}

void ASTUGameModeBase::ResetPlayers()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void ASTUGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller
		->
		GetPawn()
	)
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void ASTUGameModeBase::CreateTeamsInfo()
{
	if (!GetWorld()) return;

	//TArray<ASTUPlayerStart> PlayerStarts;
	//FindComponentByClass(PlayerStarts);

	int32 TeamID = 1;


	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
		SetPlayerColor(Controller);
		TeamID = TeamID == 1 ? 2 : 1;
	}
}

FLinearColor ASTUGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	if (TeamID - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID - 1];
	}
	UE_LOG(LogTemp, Warning, TEXT("No color for team id: %i, set to default: %s"), TeamID,
	       *GameData.DefaultTeamColor.ToString());
	return GameData.DefaultTeamColor;
}

void ASTUGameModeBase::SetPlayerColor(AController* Controller)
{
	if (!Controller) return;

	const auto Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());
	if (!Character) return;

	const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
	if (!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}
