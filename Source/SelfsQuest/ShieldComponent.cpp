// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldComponent.h"

UShieldComponent::UShieldComponent()
{
    Owner = GetOwner();
}

void UShieldComponent::DoAction()
{
    if (Owner && ShieldActorClass)
    {
        ShieldActor = GetWorld()->SpawnActor<AActor>(ShieldActorClass, Owner->GetActorLocation(), Owner->GetActorRotation());
        ShieldActor->SetOwner(Owner);
        ShieldActor->AttachToActor(Owner, FAttachmentTransformRules::KeepWorldTransform);
    }

}

void UShieldComponent::StopAction()
{
    if (ShieldActor)
    {
        ShieldActor->Destroy();
        ShieldActor = nullptr;
    }
}