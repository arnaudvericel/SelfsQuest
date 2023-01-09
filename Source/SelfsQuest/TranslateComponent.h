// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TranslateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SELFSQUEST_API UTranslateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTranslateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor* Owner;

	// Translation
	UPROPERTY(EditAnywhere, Category = "Translation")
	FVector TranslationDirection;
	UPROPERTY(EditAnywhere, Category = "Translation")
	float TranslationVelocity;

	bool CanTranslate;

	UPROPERTY(EditAnywhere, Category = "Translation | Stop Condition")
	bool StopNearPlayer;
	UPROPERTY(EditAnywhere, Category = "Translation | Stop Condition")
	float DistanceTriggerStop;
	class AShipCharacter* Player;

	void CheckDistanceToTarget();
};
