// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STU_FindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTU_FindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	USTU_FindEnemyService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
