// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()

public:
	ASTUBasePickup();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RespawnTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	bool CouldBeTakenTest = true;

	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


public:
	virtual void Tick(float DeltaTime) override;
	bool CouldBeTaken() const;
private:
	void PickupWasTaken();
	void Respawn();
	void GenerateRotationYaw();
	float RotationYaw = 0.0f;
	FTimerHandle RespawnTimerHandle;
	virtual bool GivePickupTo(APawn* PlayerPawn);
};
