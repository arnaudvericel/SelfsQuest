// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGameMode.h"

void UShipComponent::BeginPlay()
{
	Super::BeginPlay();

	ShooterGameMode = Cast<AShooterGameMode>(UGameplayStatics::GetGameMode(this));
}

void UShipComponent::DoAction()
{
	// nothing to do
}

void UShipComponent::StopAction()
{
	// nothing to do
}

