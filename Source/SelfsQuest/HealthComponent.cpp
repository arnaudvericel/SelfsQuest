// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGameMode.h"
#include "HealthBar.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100.f;

	RegenHealth = false;
	RegenPerTick = 10.f;
	RegenTickDuration = 0.5f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	ShooterGameMode = Cast<AShooterGameMode>(UGameplayStatics::GetGameMode(this));

	if (RegenHealth) GetWorld()->GetTimerManager().SetTimer(RegenTimerHandle, this, &UHealthComponent::HealTick, RegenTickDuration, true);
}

void UHealthComponent::HealTick()
{
	if (Health < MaxHealth)
	{
		if (RegenPerTick >= 0)
		{
			Health += RegenPerTick;
			if (HealthBar) HealthBar->Update(GetHealthPercent());
		}
	}
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	Health -= Damage;
	if (HealthBar) HealthBar->Update(GetHealthPercent());

	if (Health <= 0)
	{
		if (ShooterGameMode) ShooterGameMode->ActorDied(DamagedActor);
	}
}

float UHealthComponent::GetHealthPercent() const
{
	return Health / MaxHealth;
}

bool UHealthComponent::IsAlive() const
{
	return Health > 0.;
}