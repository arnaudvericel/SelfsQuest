// Fill out your copyright notice in the Description page of Project Settings.


#include "Debris.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADebris::ADebris()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FadeTimer = 2.f;
	ImpulseNorm = 200.f;
	RotationImpulseNorm = 20.f;
}

// Called when the game starts or when spawned
void ADebris::BeginPlay()
{
	Super::BeginPlay();

	GetComponents(UStaticMeshComponent::StaticClass(), Pieces);

	for (UActorComponent* Comp : Pieces)
	{
		if (auto DebrisPiece = Cast<UStaticMeshComponent>(Comp))
		{
			FVector ImpulseDirection = FVector(FMath::RandRange(-1.f, 1.f), FMath::RandRange(-1.f, 1.f), 0.f);
			bool ImpulseOk = ImpulseDirection.Normalize();
			if (ImpulseOk) DebrisPiece->AddImpulse(ImpulseDirection * ImpulseNorm);
			//
			FVector RotationImpulseDirection = FVector(FMath::RandRange(-1.f, 1.f), FMath::RandRange(-1.f, 1.f), FMath::RandRange(-1.f, 1.f));
			DebrisPiece->AddAngularImpulseInDegrees(RotationImpulseDirection * RotationImpulseNorm);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(FadeTimerHandle, this, &ADebris::Fade, FadeTimer);
}

void ADebris::Fade()
{
	Destroy();
}

// Called every frame
void ADebris::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ShrinkPieces(DeltaTime);
}

void ADebris::ShrinkPieces(float DeltaTime)
{
	for (UActorComponent* Comp : Pieces)
	{
		if (auto DebrisPiece = Cast<UStaticMeshComponent>(Comp))
		{
			if (FadeTimer > 0)
			{
				FVector Scale = DebrisPiece->GetRelativeScale3D();
				Scale -= 2.f * Scale * DeltaTime / FadeTimer;
				DebrisPiece->SetRelativeScale3D(Scale);
			}
		}
	}
}