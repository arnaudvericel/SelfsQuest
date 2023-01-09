// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserBeam.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "ShooterGameMode.h"

// Sets default values
ALaserBeam::ALaserBeam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCollider;

	DefaultDamage = 15.f;
	DamageTickTimer = 0.1;
}

// Called when the game starts or when spawned
void ALaserBeam::BeginPlay()
{	
	Super::BeginPlay();

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ALaserBeam::OnBeginOverlap);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ALaserBeam::OnEndOverlap);

	ShooterGameMode = Cast<AShooterGameMode>(UGameplayStatics::GetGameMode(this));

	CheckInitOverlap();
}

void ALaserBeam::CheckInitOverlap()
{
	AActor* MyOwner = GetOwner();
	TSet<AActor*> OverlappingActors;
	BoxCollider->GetOverlappingActors(OverlappingActors);

	for (AActor* ActorToDamage : OverlappingActors)
	{
		if (ActorToDamage != MyOwner && ActorToDamage != this)
		{
			InitTickDamage(ActorToDamage);
		}
	}
}

void ALaserBeam::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		return;
	}

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();
	
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		if (GetActorInBeamIndex(OtherActor) < 0)
		{
			InitTickDamage(OtherActor);
		}
	}
}

void ALaserBeam::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	int ActorIndex = GetActorInBeamIndex(OtherActor);
	if (ActorIndex >= 0)
	{
		FTimerHandle TimerHandle = DamageTimerHandles[ActorIndex];
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

		DamageTimerHandles.RemoveAt(ActorIndex);
		ActorsInBeam.RemoveAt(ActorIndex);
	}
}

void ALaserBeam::InitTickDamage(AActor* ActorToDamage)
{
	FTimerHandle TimerHandle;
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "DoDamage", ActorToDamage);

	ActorsInBeam.Add(ActorToDamage);
	DamageTimerHandles.Add(TimerHandle);

	DoDamage(ActorToDamage);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, DamageTickTimer, true);
}

void ALaserBeam::DoDamage(AActor* ActorToDamage)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		return;
	}

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	float DamageToApply = Damage;
	if (ShooterGameMode) DamageToApply *= ShooterGameMode->GetDamageMultiplier(); 

	if (MyOwnerInstigator) UGameplayStatics::ApplyDamage(ActorToDamage, DamageToApply, MyOwnerInstigator, MyOwner, DamageTypeClass);

	//if (HitSoundEffect) UGameplayStatics::PlaySoundAtLocation(this, HitSoundEffect, GetActorLocation());
}

int ALaserBeam::GetActorInBeamIndex(AActor* Actor) const
{
	for (int i=0; i<ActorsInBeam.Num(); i++)
	{
		if (Actor == ActorsInBeam[i])
		{
			return i;
		}
	}
	return -1;
}

void ALaserBeam::SetDamage(float InDamage)
{
	if (InDamage >= 0)
	{
		Damage = InDamage;
	}
	else
	{
		Damage = DefaultDamage;
	}
}