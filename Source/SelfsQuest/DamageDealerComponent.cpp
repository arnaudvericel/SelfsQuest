// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageDealerComponent.h"

UDamageDealerComponent::UDamageDealerComponent()
{
    BaseDamage = 40.f;
}

void UDamageDealerComponent::SetBaseDamage(float InBaseDamage)
{
    if (InBaseDamage >= 0.)
    {
        BaseDamage = InBaseDamage;
    }
}
