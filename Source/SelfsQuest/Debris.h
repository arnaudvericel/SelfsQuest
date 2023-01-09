// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Debris.generated.h"

UCLASS()
class SELFSQUEST_API ADebris : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADebris();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Fade();
	void ShrinkPieces(float DeltaTime);

	UPROPERTY(EditDefaultsOnly, Category = "Fading")
	float FadeTimer;
	UPROPERTY(EditDefaultsOnly, Category = "Fading")
	float ImpulseNorm;
	UPROPERTY(EditDefaultsOnly, Category = "Fading")
	float RotationImpulseNorm;
	FTimerHandle FadeTimerHandle;

	TArray<class UActorComponent*> Pieces;

};
