// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShipComponent.h"
#include "ZoopComponent.generated.h"

enum ZoopState
{
	Off,
	On
};

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SELFSQUEST_API UZoopComponent : public UShipComponent
{
	GENERATED_BODY()

public:
	UZoopComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void DoAction() override;
	virtual void StopAction() override;

protected:
	virtual void BeginPlay() override;

private:
	ZoopState State;
	class AShipCharacter* Owner;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ZoopDuration;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float ZoopLength;

	float ZoopXDirection;
	float DegreesPerSec;
	float DegreesRotated;
	bool OnCooldown;

	float ZoopTimer;
	FTimerHandle ZoopTimerHandle;

	void Roll(float DeltaTime);
	void Translate(float DeltaTime);

	UFUNCTION()
	void ResetCooldown();
	void SetRollDuration();
};
