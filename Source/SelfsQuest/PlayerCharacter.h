// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShipCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SELFSQUEST_API APlayerCharacter : public AShipCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	void Tick(float DeltaTime);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	void BendTime();
	UFUNCTION()
	void StopBendTime();
	FTimerHandle BendTimerHandle;
	bool CanBendTime;
	UPROPERTY(EditAnywhere, Category = "Motion")
	float BendTimeDuration;
	UPROPERTY(EditAnywhere, Category = "Motion")
	float BendTimeFactor;

	// Motion animation control
	UPROPERTY(EditAnywhere, Category = "Motion")
	float YawMaxRotation;
	UPROPERTY(EditAnywhere, Category = "Motion")
	float YawInterpSpeed;

	class AShooterGameMode* ShooterGameMode;

	UFUNCTION()
	void GotHit(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);

	void RotateTowards(FVector TargetLocation);
	float GetCorrectYawAngle(float InYawAngle);
};
