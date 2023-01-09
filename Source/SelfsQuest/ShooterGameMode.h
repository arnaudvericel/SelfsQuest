// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SELFSQUEST_API AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooterGameMode();

	void ActorDied(AActor* DeadActor);
	void PlayerGotHIt();
	
	float GetDamageMultiplier() const;

protected:
	virtual void BeginPlay() override;

private:
	// Damage multiplier combo
	UPROPERTY(EditAnywhere)
	float BaseDamageMultiplier;
	float DamageMultiplier;
	UPROPERTY(EditAnywhere)
	float DamageMultiplierTick;
	void IncreaseDamageMultiplier();
	void ResetDamageMultiplier();
};
