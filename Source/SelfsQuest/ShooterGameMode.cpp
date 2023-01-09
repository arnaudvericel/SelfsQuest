// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"
#include "EnemyCharacter.h"
#include "DestructibleDecor.h"

AShooterGameMode::AShooterGameMode()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BaseDamageMultiplier = 1.f;
    DamageMultiplierTick = 0.1f;
}

void AShooterGameMode::BeginPlay()
{
    Super::BeginPlay();

    ResetDamageMultiplier();
}

void AShooterGameMode::ActorDied(AActor* DeadActor)
{
    if (AEnemyCharacter* EnemyActor = Cast<AEnemyCharacter>(DeadActor))
    {
        EnemyActor->HandleDestruction();
        IncreaseDamageMultiplier();
    }
    else if (ADestructibleDecor* Decor = Cast<ADestructibleDecor>(DeadActor))
    {
        Decor->Destroy();
    }
}

void AShooterGameMode::PlayerGotHIt()
{
    ResetDamageMultiplier();
}

void AShooterGameMode::IncreaseDamageMultiplier()
{
    DamageMultiplier += DamageMultiplierTick;
}

void AShooterGameMode::ResetDamageMultiplier()
{
    DamageMultiplier = BaseDamageMultiplier;
}

float AShooterGameMode::GetDamageMultiplier() const
{
    return DamageMultiplier;
}