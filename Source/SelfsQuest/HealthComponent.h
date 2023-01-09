// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SELFSQUEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;
	bool IsAlive() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	class AShooterGameMode* ShooterGameMode;
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);

	// Health
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth;
	float Health;

	// Health Regeneration
	UPROPERTY(EditAnywhere, Category = "Health | Regen")
	bool RegenHealth;
	UPROPERTY(EditAnywhere, Category = "Health | Regen")
	float RegenPerTick;
	UPROPERTY(EditAnywhere, Category = "Health | Regen")
	float RegenTickDuration;
	FTimerHandle RegenTimerHandle;
	void HealTick();

	// Health Bar
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	class UHealthBar* HealthBar;
};
