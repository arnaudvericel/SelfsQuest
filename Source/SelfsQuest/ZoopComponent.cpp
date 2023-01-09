// Fill out your copyright notice in the Description page of Project Settings.


#include "ZoopComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShipCharacter.h"

UZoopComponent::UZoopComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    ZoopDuration = 0.2f;
    ZoopLength = 1500.f;
    ZoopXDirection = 0.f;
    DegreesPerSec = 0.f;
    DegreesRotated = 0.f;
    OnCooldown = false;
    ZoopTimer = 0.5f;
}

void UZoopComponent::BeginPlay()
{
    Super::BeginPlay();

    Owner = Cast<AShipCharacter>(GetOwner());
    State = ZoopState::Off;
}

void UZoopComponent::DoAction()
{
    Super::DoAction();

    if (!OnCooldown)
    {
        if (Owner) ZoopXDirection = FMath::Sign(Owner->GetInputAxisValue(TEXT("Right")));

        if (ZoopXDirection != 0)
        {
            State = ZoopState::On;
            OnCooldown = true;
            DegreesRotated = 0.f;
            SetRollDuration();
            if (Owner) Owner->SetFlyInputsEnabled(false);
        }
        else
        {
            StopAction();
        }
    }
}

void UZoopComponent::SetRollDuration()
{
    if (ZoopDuration > 0)
    {
        DegreesPerSec = 360. / ZoopDuration;
    }
    else
    {
        DegreesPerSec = 0.f;
    }
}

void UZoopComponent::StopAction()
{
    Super::StopAction();

    // buffs + timer

    State = ZoopState::Off;
    if (Owner) Owner->SetFlyInputsEnabled(true);
    GetWorld()->GetTimerManager().SetTimer(ZoopTimerHandle, this, &UZoopComponent::ResetCooldown, ZoopTimer, false);
}

void UZoopComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    switch (State)
    {
    case ZoopState::Off:
        // do nothing
        break;
    
    case ZoopState::On:
        Roll(DeltaTime);
        Translate(DeltaTime);
        break;
    }
}

void UZoopComponent::Roll(float DeltaTime)
{
    if (Owner)
    {
        FRotator RotationToApply = FRotator(0., 0., ZoopXDirection * DegreesPerSec * DeltaTime);
        Owner->AddActorLocalRotation(RotationToApply);
        DegreesRotated += FMath::Abs(RotationToApply.Roll);

        if (DegreesRotated >= 360.) StopAction();
    }
    else
    {
        StopAction();    
    }
}

void UZoopComponent::Translate(float DeltaTime)
{
    if (Owner)
    {
        FVector MovementDirection = FVector(0., ZoopXDirection, 0.);
        Owner->AddActorWorldOffset(MovementDirection * DeltaTime * ZoopLength);
    }
    else
    {
        StopAction();
    }
}

void UZoopComponent::ResetCooldown()
{
    OnCooldown = false;
}