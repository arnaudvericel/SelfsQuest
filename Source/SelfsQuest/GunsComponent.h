// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageDealerComponent.h"
#include "GunsComponent.generated.h"

/* Structure that defines the guns settings -- can be passed on to the component for quick and easy configuration, e.g. when the gamemode spawns enemies */
USTRUCT(BlueprintType)
struct FGunsSettings
{
    GENERATED_BODY()

public:
	/* Default constructor */
	FGunsSettings() : CanShoot(false), FireRate(1.0f), BaseDamage(30.0f) {}

    /** Should the component be activated */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool CanShoot;

    /** Fire rate value */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FireRate;

	/** Base damage value */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseDamage;
};

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SELFSQUEST_API UGunsComponent : public UDamageDealerComponent
{
	GENERATED_BODY()

public:
	UGunsComponent();

	UFUNCTION(BlueprintCallable)
	void Setup(FGunsSettings& GunsSettings);

	virtual void DoAction() override;
	virtual void StopAction() override;

protected:
	virtual void BeginPlay() override;

private:
	void SetActiveSpawn();
	void FireProjectile();

	class AShipCharacter* Owner;
	class AShooterGameMode* ShooterGameMode;

	// Projectile spawn point
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SpawnPointRight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SpawnPointLeft;
	USceneComponent* ActiveSpawn;
	bool IsFiringOnTheRight;

	// Projectile to shoot
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectileBase> ProjectileClass;

	// Fire rate management
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRate;
	FTimerHandle FireTimerHandle;

	// effects
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class USoundBase* FireSoundEffect;
};
