// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "STUGameModeBase.h"
#include "STUUtils.h"


// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);
	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
	}
}


void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage,
                                          const UDamageType* DamageType, AController* InstigatedBy,
                                          AActor* DamageCauser)
{
	GetWorld()->GetTimerManager().ClearTimer(Handle);
	
	if (Damage <= 0.0f || IsDead()) return;
if(InstigatedBy && UGameplayStatics::GetPlayerController(GetWorld(),0) && InstigatedBy == UGameplayStatics::GetPlayerController(GetWorld(),0))
{
	DamageDone = Damage;
	UE_LOG(LogTemp, Display, TEXT("Damage = %f"), Damage);
} else
{
	DamageDone = 0.0f;
}

	
	SetHealth(Health - Damage);

	if (IsDead())
	{
		Killed(InstigatedBy);
		OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &USTUHealthComponent::AutoHealFunction, HealUpdateTime,
		                                       true, HealDelay);
	}

	PlayCameraShake();
}

void USTUHealthComponent::AutoHealFunction()
{
	SetHealth(Health + HealModifier);

	if (FMath::IsNearlyEqual(Health, MaxHealth))
	{
		GetWorld()->GetTimerManager().ClearTimer(Handle);
	}
}

void USTUHealthComponent::PlayCameraShake()
{
	if (IsDead()) return;
	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void USTUHealthComponent::Killed(AController* KillerController)
{
	const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto Player = Cast<APawn>(GetOwner());
	const auto VictimController = Player ? Player->Controller : nullptr;

	GameMode->Killed(KillerController, VictimController);
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;
	
	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}
