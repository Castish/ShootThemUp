// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
};
