// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/STUHealthPickup.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"

class USTUHealthComponent;

bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;
	const auto CurrentHealth = HealthComponent->GetHealth();
	if (CurrentHealth == HealthComponent->GetMaxHealth()) return false;
	HealthComponent->SetHealth(CurrentHealth + HealModifier);
	return true;
}
