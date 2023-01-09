// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserBeam.generated.h"

UCLASS()
class SELFSQUEST_API ALaserBeam : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaserBeam();

	void SetDamage(float InDamage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// constructor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollider;

	class AShooterGameMode* ShooterGameMode;
	
	UFUNCTION() // has to be to add it to the deleguate
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	void CheckInitOverlap();

	void InitTickDamage(AActor* ActorToDamage);
	UFUNCTION()
	void DoDamage(AActor* ActorToDamage);

	int GetActorInBeamIndex(AActor* Actor) const;

	// Laser damage
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float DefaultDamage;
	float Damage;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float DamageTickTimer;

	// Actors touched by the laser
	TArray<FTimerHandle> DamageTimerHandles;
	TArray<AActor*> ActorsInBeam;

	// Effects
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class USoundBase* HitSoundEffect;
};
