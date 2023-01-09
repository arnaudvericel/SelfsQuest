// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GunsComponent.h"
#include "Debris.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DeathEffectScale = 1.0f;
    CanFireGuns = false;
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (CanFireGuns)
    {
        FireGuns();
    }
}

void AEnemyCharacter::HandleDestruction()
{
	if (DeathEffect) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathEffect, GetActorLocation(), FRotator::ZeroRotator, FVector(DeathEffectScale));
	if (DeathSoundEffect) UGameplayStatics::PlaySoundAtLocation(this, DeathSoundEffect, GetActorLocation());
	if (DebrisClass) GetWorld()->SpawnActor<ADebris>(DebrisClass, GetActorLocation(), GetActorRotation());
	Destroy();
}