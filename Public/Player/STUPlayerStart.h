// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "STUPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerStart : public APlayerStart
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditInstanceOnly, Category = "TeamID")
	int32 TeamID = 1;

public:
	int32 GetTeamID() const {return TeamID;} 
};
