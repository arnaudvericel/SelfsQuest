// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageDealerComponent.h"
#include "LaserComponent.generated.h"

class USoundBase;
class UParticleSystem;
/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SELFSQUEST_API ULaserComponent : public UDamageDealerComponent
{
	GENERATED_BODY()

public:
	ULaserComponent();

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
