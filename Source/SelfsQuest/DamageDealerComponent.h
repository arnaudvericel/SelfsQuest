// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShipComponent.h"
#include "DamageDealerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SELFSQUEST_API UDamageDealerComponent : public UShipComponent
{
	GENERATED_BODY()

public:
	UDamageDealerComponent();

	UFUNCTION(BlueprintCallable)
	void SetBaseDamage(float InBaseDamage);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float BaseDamage;
};
