// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"
#include "Components/ProgressBar.h"

void UHealthBar::Update(float InHealthPercent)
{
    if (InHealthPercent < 0) { InHealthPercent = 0.f; }

    HealthBar->SetPercent(InHealthPercent);
}