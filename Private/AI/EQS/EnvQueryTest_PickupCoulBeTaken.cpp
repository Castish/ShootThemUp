// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/EnvQueryTest_PickupCoulBeTaken.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/STUBasePickup.h"

UEnvQueryTest_PickupCoulBeTaken::UEnvQueryTest_PickupCoulBeTaken(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickupCoulBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{

	const auto DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);

	const bool WantsItTakable = BoolValue.GetValue();
	
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());
		const auto PickupActor = Cast<ASTUBasePickup>(ItemActor);
		if(!PickupActor) continue;

		const auto CouldBeTaken = PickupActor->CouldBeTaken();
		It.SetScore(TestPurpose, FilterType, CouldBeTaken, WantsItTakable);
	}
		
}
