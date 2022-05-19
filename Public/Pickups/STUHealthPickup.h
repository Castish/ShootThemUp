// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickup : public ASTUBasePickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Pickup", meta=(ClampMin = "1", ClampMax = "100"))
	int32 HealModifier = 50;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
