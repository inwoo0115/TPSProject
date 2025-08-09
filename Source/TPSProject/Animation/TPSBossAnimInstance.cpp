// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/TPSBossAnimInstance.h"
#include "TPSBossAnimInstance.h"
#include "Character/TPSBossCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTPSBossAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ATPSBossCharacter>(GetOwningActor());

	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UTPSBossAnimInstance::NativeUpdateAnimation(float DeltaSceonds)
{
	Super::NativeUpdateAnimation(DeltaSceonds);

	if (Movement)
	{
		Velocity = Owner->GetVelocity().Length();
		bIsFalling = Movement->IsFalling();
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
