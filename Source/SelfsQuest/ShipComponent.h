// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShipComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SELFSQUEST_API UShipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	virtual void DoAction();
	virtual void StopAction();

protected:
	class AShooterGameMode* ShooterGameMode;

	virtual void BeginPlay() override;
};
