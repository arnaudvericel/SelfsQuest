// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShipComponent.h"
#include "ShieldComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SELFSQUEST_API UShieldComponent : public UShipComponent
{
	GENERATED_BODY()

public:
	UShieldComponent();

	virtual void DoAction() override;
	virtual void StopAction() override;

private:
	class AActor* Owner;
	UPROPERTY(EditAnywhere, Category = "Shield")
	TSubclassOf<AActor> ShieldActorClass;
	AActor* ShieldActor;
};
