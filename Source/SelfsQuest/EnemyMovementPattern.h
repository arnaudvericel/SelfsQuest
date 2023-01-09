// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyMovementPattern.generated.h"

enum PatternPoint
{
	Up,
	Down,
	Left,
	Right
};

struct PatternPointParams
{
	float Amplitude;
	float Frequency;
	PatternPoint NextPoint;
	FVector DirectionToNextPoint;

	PatternPointParams(PatternPoint Next, FVector DirToNext, float Amp, float Freq)
	{
		Amplitude = Amp;
		NextPoint = Next;
		DirectionToNextPoint = DirToNext;
		Frequency = Freq;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SELFSQUEST_API UEnemyMovementPattern : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyMovementPattern();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Translation pattern
	UPROPERTY(EditAnywhere, Category = "Movement | Pattern | Translation")
	bool MoveUpDown;
	UPROPERTY(EditAnywhere, Category = "Movement | Pattern | Translation")
	bool MoveRightLeft;
	UPROPERTY(EditAnywhere, Category = "Movement | Pattern | Translation")
	float UpDownAmplitude;
	UPROPERTY(EditAnywhere, Category = "Movement | Pattern | Translation")
	float RightLeftAmplitude;
	UPROPERTY(EditAnywhere, Category = "Movement | Pattern | Translation")
	float UpDownFrequency;
	UPROPERTY(EditAnywhere, Category = "Movement | Pattern | Translation")
	float RightLeftFrequency;

	// Rotation pattern
	UPROPERTY(EditAnywhere, Category = "Movement | Pattern | Rotation")
	bool RotateAroundPoint;
	UPROPERTY(EditAnywhere, Category = "Movement | Pattern | Rotation")
	bool RotationIsClockWise;
	UPROPERTY(EditAnywhere, Category = "Movement | Pattern | Rotation")
	float DistanceToPivot;
	UPROPERTY(EditAnywhere, Category = "Movement | Pattern | Rotation")
	float RotationFrequency;

	TMap<PatternPoint,PatternPointParams> TranslationPattern;
	PatternPoint CurrentPoint;
	float CurrentPointDistance;
	void SetupTranslationPattern();

	void DoTranslationPattern(float DeltaTime);
};
