// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipCharacter.h"
#include "ShipComponent.h"
#include "GunsComponent.h"
#include "LaserComponent.h"
#include "ShieldComponent.h"
#include "ZoopComponent.h"
#include "ShipController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "HealthComponent.h"

// Sets default values
AShipCharacter::AShipCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Mesh"));
	ShipMesh->SetupAttachment(RootComponent);

	GunsRightFirePoint = CreateDefaultSubobject<USceneComponent>(TEXT("Guns Right Fire Point"));
    GunsRightFirePoint->SetupAttachment(ShipMesh);

	GunsLeftFirePoint = CreateDefaultSubobject<USceneComponent>(TEXT("Guns Left Fire Point"));
    GunsLeftFirePoint->SetupAttachment(ShipMesh);

    LaserFirePoint = CreateDefaultSubobject<USceneComponent>(TEXT("Laser Fire Point"));
    LaserFirePoint->SetupAttachment(ShipMesh);

	RollMaxRotation = 0.f;
	RollInterSpeed = 4.f;
	FlyInputsEnabled = true;
}

// Called when the game starts or when spawned
void AShipCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Guns = Cast<UShipComponent>(GetComponentByClass(UGunsComponent::StaticClass()));
	Laser = Cast<UShipComponent>(GetComponentByClass(ULaserComponent::StaticClass()));
	Shield = Cast<UShipComponent>(GetComponentByClass(UShieldComponent::StaticClass()));
	Zoop = Cast<UShipComponent>(GetComponentByClass(UZoopComponent::StaticClass()));

	ShipController = Cast<AShipController>(GetController());
}

// Called to bind functionality to input
void AShipCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Binding axis input to the character
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AShipCharacter::FlyForward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AShipCharacter::FlyRight);

	// Binding actions input to the character
	PlayerInputComponent->BindAction(TEXT("FireGuns"), EInputEvent::IE_Pressed, this, &AShipCharacter::FireGuns);
	PlayerInputComponent->BindAction(TEXT("FireGuns"), EInputEvent::IE_Released, this, &AShipCharacter::StopGuns);
	PlayerInputComponent->BindAction(TEXT("FireLaser"), EInputEvent::IE_Pressed, this, &AShipCharacter::FireLaser);
	PlayerInputComponent->BindAction(TEXT("FireLaser"), EInputEvent::IE_Released, this, &AShipCharacter::StopLaser);
	PlayerInputComponent->BindAction(TEXT("Shield"), EInputEvent::IE_Pressed, this, &AShipCharacter::ActivateShield);
	PlayerInputComponent->BindAction(TEXT("Shield"), EInputEvent::IE_Released, this, &AShipCharacter::DeactivateShield);
	PlayerInputComponent->BindAction(TEXT("Zoop"), EInputEvent::IE_Pressed, this, &AShipCharacter::DoZoop);
}

void AShipCharacter::FlyForward(float AxisValue)
{
	if (FlyInputsEnabled)
	{
		AddMovementInput(GetActorForwardVector() * AxisValue);
	}
}

void AShipCharacter::FlyRight(float AxisValue)
{
	if (FlyInputsEnabled)
	{
		AddMovementInput(GetActorRightVector() * AxisValue);
		//
		FRotator TargetRoll = FRotator(0.f, 0.f, RollMaxRotation * AxisValue);
		FRotator RollRotation = FMath::RInterpTo(GetActorRotation(), TargetRoll, UGameplayStatics::GetWorldDeltaSeconds(this), RollInterSpeed);
		SetActorRotation(RollRotation);
	}
}

void AShipCharacter::FireGuns()
{
	if (Guns && Guns->IsActive())
	{
		Guns->DoAction();
	}
}

void AShipCharacter::StopGuns()
{
	if (Guns && Guns->IsActive())
	{
		Guns->StopAction();
	}
}

void AShipCharacter::FireLaser()
{
	if (Laser && Laser->IsActive())
	{
		Laser->DoAction();
	}
}

void AShipCharacter::StopLaser()
{
	if (Laser && Laser->IsActive())
	{
		Laser->StopAction();
	}
}

void AShipCharacter::ActivateShield()
{
	if (Shield && Shield->IsActive())
	{
		Shield->DoAction();
	}
}

void AShipCharacter::DeactivateShield()
{
	if (Shield && Shield->IsActive())
	{
		Shield->StopAction();
	}
}

void AShipCharacter::DoZoop()
{
	if (Zoop && Zoop->IsActive())
	{
		Zoop->DoAction();
	}
}

void AShipCharacter::SetFlyInputsEnabled(bool InFlyInputsEnabled)
{
	FlyInputsEnabled = InFlyInputsEnabled;
}