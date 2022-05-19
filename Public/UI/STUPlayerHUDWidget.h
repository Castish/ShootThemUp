// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "Components/STUHealthComponent.h"
#include "STUPlayerHUDWidget.generated.h"


UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void OnTakeDamage();

	UFUNCTION(BlueprintCallable, Category="UI")
	int32 GetKillsNum();

	UFUNCTION(BlueprintCallable, Category="UI")
	int32 GetDeathsNum();

	UFUNCTION(BlueprintCallable, Category="UI")
	int32 GetRoundNum();

	UFUNCTION(BlueprintCallable, Category="UI")
	int32 GetMaxRounds();


	UFUNCTION(BlueprintCallable, Category="UI")
	int32 GetTimeOnRoundLeft();
	
	UFUNCTION(BlueprintCallable, Category="UI")
	float GetDamageDone();

protected:
	virtual void NativeOnInitialized() override;

private:
	void OnHealthChanged(float Health, float HealthDelta);
	void OnNewPawn(APawn* NewPawn);
	

};


