// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/STUAmmoAmountDecorator.h"

#include "AIController.h"
#include "STUUtils.h"
#include "STUCoreTypes.h"
#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"

USTUAmmoAmountDecorator::USTUAmmoAmountDecorator()
{
	NodeName = "Need Ammo";
}

bool USTUAmmoAmountDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;
	
	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->NeedAmmo(WeaponType);
}
