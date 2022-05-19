// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"

class UCameraShakeBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USTUHealthComponent();
	UFUNCTION(BlueprintCallable, Category= "Health")
	bool IsDead() const { return Health <= 0.0f; }

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHealth = 100.f;

	UFUNCTION(BlueprintCallable, Category= "Health")
	float GetHealthPercent() const { return Health / MaxHealth; }
	
	float GetDamageDone() {return DamageDone;}
	float GetHealth() const { return Health; }
	float GetMaxHealth() const { return MaxHealth; }

	void SetHealth(float NewHealth);
protected:
	// Called when the game starts


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Heal")
	bool AutoHeal = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Heal")
	float HealUpdateTime = 0.3f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Heal")
	float HealDelay = 3.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Heal")
	float HealModifier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "VFX")
	TSubclassOf<UCameraShakeBase> CameraShake;
	virtual void BeginPlay() override;


private:
	float Health = 0.0f;
	float DamageDone = 0.0f;
	FTimerHandle Handle;
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	                     class AController* InstigatedBy, AActor* DamageCauser);

	
	UFUNCTION()
	void AutoHealFunction();
	void PlayCameraShake();

	void Killed(AController* KillerController);
};
