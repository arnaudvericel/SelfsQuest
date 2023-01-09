// Fill out your copyright notice in the Description page of Project Settings.


#include "TranslateComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShipCharacter.h"

// Sets default values for this component's properties
UTranslateComponent::UTranslateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CanTranslate = true;
	StopNearPlayer = false;
	DistanceTriggerStop = 1000.f;
}


// Called when the game starts
void UTranslateComponent::BeginPlay()
{
	Super::BeginPlay();

	// if the normalization failed, the component deactivates
	CanTranslate = TranslationDirection.Normalize();
	Owner = GetOwner();
	Player = Cast<AShipCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}


// Called every frame
void UTranslateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsActive() && CanTranslate)
	{
		GetOwner()->AddActorWorldOffset(TranslationDirection * DeltaTime * TranslationVelocity);
		CheckDistanceToTarget();
	}
}

void UTranslateComponent::CheckDistanceToTarget()
{
	if (Player && StopNearPlayer)
	{
		float DistanceToTarget = FMath::Abs(Owner->GetActorLocation().X - Player->GetActorLocation().X);
		if (DistanceToTarget <= DistanceTriggerStop)
		{
			CanTranslate = false;
		}
	}
}