// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"
#include "Player/STUPlayerState.h"
#include "STUGameModeBase.h"
#include "Weapon/STURifleWeapon.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}

bool USTUPlayerHUDWidget::GetAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;
	return WeaponComponent->GetCurrentAmmoData(AmmoData);
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}


int32 USTUPlayerHUDWidget::GetKillsNum()
{
	const auto Controller = GetOwningPlayer();
	if (!Controller) return 90;
	const auto GameMode = Controller->GetPlayerState<ASTUPlayerState>();
	if (!GameMode) return 91;
	return GameMode->GetKillsNum();
}

int32 USTUPlayerHUDWidget::GetDeathsNum()
{
	const auto Controller = GetOwningPlayer();
	if (!Controller) return 90;
	const auto GameMode = Controller->GetPlayerState<ASTUPlayerState>();
	if (!GameMode) return 91;
	return GameMode->GetDeathsNum();
}

int32 USTUPlayerHUDWidget::GetRoundNum()
{
	const auto GameMod = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMod) return 99;
	return GameMod->GetCurrentRound();
}

int32 USTUPlayerHUDWidget::GetMaxRounds()
{
	const auto GameMod = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMod) return 99;
	return GameMod->GetMaxRounds();
}


int32 USTUPlayerHUDWidget::GetTimeOnRoundLeft()
{
	const auto GameMod = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMod) return 99;
	return GameMod->GetCurrentRoundTimeLeft();
}

float USTUPlayerHUDWidget::GetDamageDone()
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent) return 0.0f;
	return HealthComponent->GetDamageDone();
}


void USTUPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
	}
}

void USTUPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta <= 0)
	{
		OnTakeDamage();
	}
}

void USTUPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(NewPawn);
	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
	}
}
