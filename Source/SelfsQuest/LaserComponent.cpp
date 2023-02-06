// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserComponent.h"
#include "LaserBeam.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGameMode.h"
#include "Particles/ParticleSystemComponent.h"

ULaserComponent::ULaserComponent()
{
    LaserTimer = 2.f;
    OverheatTimer = 3.f;
    HasOverheat = false;
    SetActive(true);
}

void ULaserComponent::Setup(FLaserSettings& LaserSettings)
{
    this->SetActive(LaserSettings.CanShoot);
    if (LaserSettings.BaseDamage >= 0.) this->BaseDamage = LaserSettings.BaseDamage;
    if (LaserSettings.LaserTimer > 0) this->LaserTimer = LaserSettings.LaserTimer;
    if (LaserSettings.OverheatTimer > 0) this->OverheatTimer = LaserSettings.OverheatTimer;
}

void ULaserComponent::DoAction()
{
    if (LaserSpawnPoint)
    {
        if (!HasOverheat)
        {
            FireLaser();
        }
        else
        {
            if (FireWhileOverheatSoundEffect) UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireWhileOverheatSoundEffect, LaserSpawnPoint->GetComponentLocation());
        }
    }
}

void ULaserComponent::FireLaser()
{
    FActorSpawnParameters SpawnParams = FActorSpawnParameters();
    SpawnParams.Owner = GetOwner();

    LaserBeam = GetWorld()->SpawnActor<ALaserBeam>(LaserBeamClass, LaserSpawnPoint->GetComponentLocation(), LaserSpawnPoint->GetComponentRotation(), SpawnParams);

    if (LaserBeam)
    {
        float DamageToApply = BaseDamage;
        if (ShooterGameMode) DamageToApply *= ShooterGameMode->GetDamageMultiplier();
        LaserBeam->SetDamage(DamageToApply);
        
        LaserBeam->AttachToComponent(LaserSpawnPoint, FAttachmentTransformRules::KeepWorldTransform);
        if (LaserSoundEffect) UGameplayStatics::PlaySoundAtLocation(GetWorld(), LaserSoundEffect, LaserSpawnPoint->GetComponentLocation());
        
        GetWorld()->GetTimerManager().SetTimer(LaserTimerHandle, this, &ULaserComponent::Overheat, LaserTimer, false);
    }
}

void ULaserComponent::StopAction()
{
    if (LaserBeam) 
    {
        LaserBeam->Destroy();
        LaserBeam = nullptr;
        GetWorld()->GetTimerManager().ClearTimer(LaserTimerHandle);
    }
}

void ULaserComponent::Overheat()
{
    StopAction();
    HasOverheat = true;
    
    if (OverheatSoundEffect) UGameplayStatics::PlaySoundAtLocation(GetWorld(), OverheatSoundEffect, LaserSpawnPoint->GetComponentLocation());
    if (OverheatEffect)
    {
        OverheatParticleSystem = UGameplayStatics::SpawnEmitterAttached(
            OverheatEffect, 
            LaserSpawnPoint, 
            NAME_None, 
            FVector::ZeroVector, 
            FRotator::ZeroRotator, 
            FVector(10.f));
    }

    GetWorld()->GetTimerManager().SetTimer(OverheatTimerHandle, this, &ULaserComponent::OverheatFinished, OverheatTimer, false);
}

void ULaserComponent::OverheatFinished()
{
    HasOverheat = false;
    if (OverheatParticleSystem) OverheatParticleSystem->DestroyComponent();
}