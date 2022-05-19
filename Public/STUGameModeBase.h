// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUCoreTypes.h"
#include "STUGameModeBase.generated.h"

class AAIController;
UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASTUGameModeBase();

	FOnMatchStateChangedSignature OnMatchStateChanged;
	
	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	virtual bool ClearPause() override;


	void Killed(AController* KillerController, AController* VictimController);
	int32 GetCurrentRound() const {return CurrentRound;}
	int32 GetCurrentRoundTimeLeft() const {return RoundCountDown;}
	int32 GetMaxRounds() const {return GameData.RoundsNum;}

	void RespawnRequest(AController* Controller);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	FGameData GameData;
private:
	ESTUMatchState MatchState = ESTUMatchState::WaitingToStart;
	int32 CurrentRound = 1;
	int32 RoundCountDown = 0;
	FTimerHandle GameRoundTimerHandle;

	void SpawnBots();
	void StartRound();
	void GameTimerUpdate();

	void ResetPlayers();
	void ResetOnePlayer(AController* Controller);

	void CreateTeamsInfo();
	FLinearColor DetermineColorByTeamID(int32 TeamID) const;
	void SetPlayerColor(AController* Controller);

	void LogPlayerInfo();

	void StartRespawn(AController* Controller);

	void GameOver();

	void SetMatchState(ESTUMatchState State);

	
};
