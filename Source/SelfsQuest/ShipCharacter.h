// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShipCharacter.generated.h"

class USceneComponent;
class UShipComponent;

UCLASS()
class SELFSQUEST_API AShipCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShipCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetFlyInputsEnabled(bool InFlyInputsEnabled);

protected:
	// Called when the game starts or when spawned()
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Motion")
	float RollMaxRotation;
	UPROPERTY(EditAnywhere, Category = "Motion")
	float RollInterSpeed;
	class AShipController* ShipController;

	UShipComponent* Guns;
	UShipComponent* Laser;
	UShipComponent* Shield;
	UShipComponent* Zoop;

	// Actions input bindings
	void FireGuns();
	void StopGuns();
	void FireLaser();
	void StopLaser();
	void ActivateShield();
	void DeactivateShield();
	void DoZoop();

private:
	// constructor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* GunsRightFirePoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* GunsLeftFirePoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* LaserFirePoint;

	// Axis input bindings
	bool FlyInputsEnabled;
	void FlyForward(float AxisValue);
	void FlyRight(float AxisValue);
};
