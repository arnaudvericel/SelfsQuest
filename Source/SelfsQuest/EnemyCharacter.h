// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShipCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SELFSQUEST_API AEnemyCharacter : public AShipCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();
	void HandleDestruction();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class ADebris> DebrisClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	bool CanFireGuns;

	// Death effects
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UParticleSystem* DeathEffect;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float DeathEffectScale;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class USoundBase* DeathSoundEffect;
};
