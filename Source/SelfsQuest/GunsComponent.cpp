// Fill out your copyright notice in the Description page of Project Settings.


#include "GunsComponent.h"
#include "ShipCharacter.h"
#include "ProjectileBase.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGameMode.h"

UGunsComponent::UGunsComponent()
{
    IsFiringOnTheRight = true;
    FireRate = 1.f;
}

void UGunsComponent::BeginPlay()
{
    Super::BeginPlay();

    ShooterGameMode = Cast<AShooterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void UGunsComponent::DoAction()
{
    Super::DoAction();

    FireProjectile();
    
    GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &UGunsComponent::FireProjectile, FireRate, true);
}

void UGunsComponent::StopAction()
{
    Super::StopAction();

    GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void UGunsComponent::FireProjectile()
{
    float DamageToApply = BaseDamage;
    if (ShooterGameMode) DamageToApply *= ShooterGameMode->GetDamageMultiplier();

    Owner = Cast<AShipCharacter>(GetOwner());

    if (Owner && ProjectileClass)
    {
        SetActiveSpawn();
        if (ActiveSpawn)
        {
            AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, ActiveSpawn->GetComponentLocation(), Owner->GetActorRotation());
            
            if (Projectile) 
            {
                Projectile->SetOwner(Owner);
                Projectile->SetDamage(DamageToApply);
                if (FireSoundEffect) UGameplayStatics::PlaySoundAtLocation(this, FireSoundEffect, ActiveSpawn->GetComponentLocation());
            }
        }
    }
}

void UGunsComponent::SetActiveSpawn()
{
    if (IsFiringOnTheRight)
    {
        ActiveSpawn = SpawnPointRight;
    }
    else
    {
        ActiveSpawn = SpawnPointLeft;
    }

    IsFiringOnTheRight = !IsFiringOnTheRight; 
}