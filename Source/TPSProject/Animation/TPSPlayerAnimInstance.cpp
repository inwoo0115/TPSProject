// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/TPSPlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "Character/TPSCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

UTPSPlayerAnimInstance::UTPSPlayerAnimInstance()
{
}

void UTPSPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ATPSCharacterPlayer>(GetOwningActor());

	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UTPSPlayerAnimInstance::NativeUpdateAnimation(float DeltaSceonds)
{
	Super::NativeUpdateAnimation(DeltaSceonds);

	if (Movement)
	{
		Velocity = Owner->GetVelocity().Length();
		bIsFalling = Movement->IsFalling();
		bIsAim = Owner->GetIsAim();
		bIsAccelerating = Movement->GetCurrentAcceleration().Length() > 0;
		Axis = Owner->GetActorTransform().InverseTransformVector(Owner->GetVelocity().GetSafeNormal(0.0001));
		bIsMontagePlaying = Montage_IsPlaying(nullptr);
		if (Owner->GetController())
		{
			FRotator ControlRotation = Owner->GetController()->GetControlRotation();

			Yaw = ControlRotation.Yaw;
			Roll = ControlRotation.Roll;
			if (ControlRotation.Pitch > 180.0)
			{
				Pitch = ControlRotation.Pitch - 360.0;
			}
			else
			{
				Pitch = ControlRotation.Pitch;
			}
		}
	}
}
