// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/STUChangeWeaponService.h"

#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUAIWeaponComponent.h"


USTUChangeWeaponService::USTUChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto AIController = OwnerComp.GetAIOwner();
	// const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if (AIController && Probability > 0 && FMath::FRand() <= Probability)
	{
		const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUAIWeaponComponent>(AIController->GetPawn());
		if (WeaponComponent)
		{
			WeaponComponent->NextWeapon();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
