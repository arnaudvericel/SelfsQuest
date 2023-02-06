// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageDealerComponent.h"
#include "LaserComponent.generated.h"

class USoundBase;
class UParticleSystem;

/* Structure that defines the laser settings -- can be passed on to the component for quick and easy configuration, e.g. when the gamemode spawns enemies */
USTRUCT(BlueprintType)
struct FLaserSettings
{
    GENERATED_BODY()

public:
	/* Default constructor */
	FLaserSettings() : CanShoot(false), BaseDamage(30.0f), LaserTimer(2.0f), OverheatTimer(3.0f) {}

    /** Should the component be activated */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool CanShoot;

	/** Base damage value */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseDamage;

	/** How long the laser can be shot before overheating */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LaserTimer;

	/** How long the laser overheats for */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float OverheatTimer;
};

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SELFSQUEST_API ULaserComponent : public UDamageDealerComponent
{
	GENERATED_BODY()

public:
	ULaserComponent();

	UFUNCTION(BlueprintCallable)
	void Setup(FLaserSettings& LaserSettings);
	virtual void DoAction() override;
	virtual void StopAction() override;

private:
	void FireLaser();
	void Overheat();
	void OverheatFinished();

	bool HasOverheat;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	USceneComponent* LaserSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class ALaserBeam> LaserBeamClass;
	ALaserBeam* LaserBeam;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float LaserTimer;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float OverheatTimer;
	FTimerHandle LaserTimerHandle;
	FTimerHandle OverheatTimerHandle;

	// effects
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* LaserSoundEffect;
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* FireWhileOverheatSoundEffect;
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* OverheatSoundEffect;
	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* OverheatEffect;
	class UParticleSystemComponent* OverheatParticleSystem;
};
