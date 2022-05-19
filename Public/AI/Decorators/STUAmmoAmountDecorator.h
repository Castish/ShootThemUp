// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUCoreTypes.h"
#include "STUAmmoAmountDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUAmmoAmountDecorator : public UBTDecorator
{
	GENERATED_BODY()
	USTUAmmoAmountDecorator();
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI")
	TSubclassOf<ASTUBaseWeapon> WeaponType;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
