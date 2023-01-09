// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "ShipController.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGameMode.h"

APlayerCharacter::APlayerCharacter()
{
    RollMaxRotation = 30.f;
	YawMaxRotation = 60.f;
	YawInterpSpeed = 1.0f;

	CanBendTime = true;
	BendTimeFactor = 0.5f;
	BendTimeDuration = 4.f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	ShooterGameMode = Cast<AShooterGameMode>(UGameplayStatics::GetGameMode(this));
	OnTakeAnyDamage.AddDynamic(this, &APlayerCharacter::GotHit);
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("BendTime"), EInputEvent::IE_Pressed, this, &APlayerCharacter::BendTime);
}

void APlayerCharacter::BendTime()
{
	if (CanBendTime)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), BendTimeFactor);
		CanBendTime = false;
		GetWorld()->GetTimerManager().SetTimer(BendTimerHandle, this, &APlayerCharacter::StopBendTime, BendTimeDuration, false);
		// + effects
	}
}

void APlayerCharacter::StopBendTime()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	CanBendTime = true;
	// + effects
}

void APlayerCharacter::GotHit(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* DamageInstigator, AActor* DamageCauser)
{
	if (ShooterGameMode && DamagedActor == this)
	{
		ShooterGameMode->PlayerGotHIt();
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ShipController)
	{
		FHitResult HitResult;
    	bool collided = ShipController->GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);

		if (collided)
        {
            //RotateTowards(HitResult.ImpactPoint); // fixme : rotate the guns only?
        }
	}
}

void APlayerCharacter::RotateTowards(FVector TargetLocation)
{
	FVector ToTarget = TargetLocation - GetActorLocation();
	ToTarget.Z = 0.f; // no motion along the z axis

	float YawAngle = GetCorrectYawAngle(ToTarget.Rotation().Yaw);
	FRotator RotatorToTarget = FRotator(0.f, YawAngle, 0.f);

	RootComponent->SetWorldRotation(FMath::RInterpTo(GetActorRotation(),
													 RotatorToTarget, 
													 UGameplayStatics::GetWorldDeltaSeconds(this), 
													 YawInterpSpeed));
}

float APlayerCharacter::GetCorrectYawAngle(float InYawAngle)
{
	float YawValue = InYawAngle;

	if (InYawAngle > YawMaxRotation)
	{
		YawValue = YawMaxRotation;
	}
	else if (InYawAngle < -YawMaxRotation)
	{
		YawValue = -YawMaxRotation;
	}

	return YawValue;
}