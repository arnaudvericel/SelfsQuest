// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleDecor.h"
#include "Components/SphereComponent.h"

// Sets default values
ADestructibleDecor::ADestructibleDecor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = Collider;
}

// Called when the game starts or when spawned
void ADestructibleDecor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructibleDecor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

