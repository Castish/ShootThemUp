// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickupCoulBeTaken.generated.h"


UCLASS()
class SHOOTTHEMUP_API UEnvQueryTest_PickupCoulBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()
	UEnvQueryTest_PickupCoulBeTaken(const FObjectInitializer& ObjectInitializer);
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
