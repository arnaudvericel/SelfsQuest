// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMovementPattern.h"

// Sets default values for this component's properties
UEnemyMovementPattern::UEnemyMovementPattern()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// translation pattern
	MoveUpDown = true;
	MoveRightLeft = true;
	UpDownAmplitude = 500.f;
	RightLeftAmplitude = 500.f;
	UpDownFrequency = 0.1f;
	RightLeftFrequency = 0.1f;

	// rotation pattern
	RotateAroundPoint = false;
	RotationIsClockWise = true;
	DistanceToPivot = 1000.f;
	RotationFrequency = 0.1f;

	CurrentPointDistance = 0.f;
}


// Called when the game starts
void UEnemyMovementPattern::BeginPlay()
{
	Super::BeginPlay();

	CurrentPoint = PatternPoint::Up;
	SetupTranslationPattern();
}

void UEnemyMovementPattern::SetupTranslationPattern()
{
	if (MoveUpDown && MoveRightLeft)
	{
		TranslationPattern.Add(PatternPoint::Up, PatternPointParams(PatternPoint::Left, FVector::LeftVector, RightLeftAmplitude, RightLeftFrequency));
		TranslationPattern.Add(PatternPoint::Left, PatternPointParams(PatternPoint::Down, FVector::BackwardVector, UpDownAmplitude, UpDownFrequency));
		TranslationPattern.Add(PatternPoint::Down, PatternPointParams(PatternPoint::Right, FVector::RightVector, RightLeftAmplitude, RightLeftFrequency));
		TranslationPattern.Add(PatternPoint::Right, PatternPointParams(PatternPoint::Up, FVector::ForwardVector, UpDownAmplitude, UpDownFrequency));
	}
	else
	{
		if (MoveUpDown)
		{
			TranslationPattern.Add(PatternPoint::Up, PatternPointParams(PatternPoint::Down, FVector::BackwardVector, UpDownAmplitude, UpDownFrequency));
			TranslationPattern.Add(PatternPoint::Down, PatternPointParams(PatternPoint::Up, FVector::ForwardVector, UpDownAmplitude, UpDownFrequency));
		}
		else if (MoveRightLeft)
		{
			TranslationPattern.Add(PatternPoint::Right, PatternPointParams(PatternPoint::Left, FVector::RightVector, RightLeftAmplitude, RightLeftFrequency));
			TranslationPattern.Add(PatternPoint::Left, PatternPointParams(PatternPoint::Right, FVector::LeftVector, RightLeftAmplitude, RightLeftFrequency));
		}
	}
}

// Called every frame
void UEnemyMovementPattern::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DoTranslationPattern(DeltaTime);
}

void UEnemyMovementPattern::DoTranslationPattern(float DeltaTime)
{
	if (IsActive() && (MoveUpDown || MoveRightLeft))
	{
		PatternPointParams CurrentPointParams = TranslationPattern[CurrentPoint];
		FVector OffsetToApply = CurrentPointParams.DirectionToNextPoint * CurrentPointParams.Amplitude * CurrentPointParams.Frequency * DeltaTime;

		GetOwner()->AddActorWorldOffset(OffsetToApply);
		CurrentPointDistance += OffsetToApply.Size();

		if (CurrentPointDistance >= CurrentPointParams.Amplitude)
		{
			CurrentPoint = CurrentPointParams.NextPoint;
			CurrentPointDistance = 0.f;
		}
	}
}
