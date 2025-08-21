// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/SpAttackAbility/TPSGrenadeMoveCharacter.h"
#include "CharacterEquipment/TPSSpAttackSkillBase.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"
#include "GameframeWork/Character.h"
#include "GameframeWork/CharacterMovementComponent.h"

UTPSGrenadeMoveCharacter::UTPSGrenadeMoveCharacter()
{
	AbilityName = FText::FromString(TEXT("Hyper-Kinetic Position Reverser"));
	AbilityDescription = FText::FromString(TEXT("Move Character to Grenade Hit Location"));

	AbilityType = EAbilityType::SpAttackAbility;
}

void UTPSGrenadeMoveCharacter::InitializeSpAttackAbility(FSpAttackSkillContext& SkillContext)
{
	Super::InitializeSpAttackAbility(SkillContext);
}

void UTPSGrenadeMoveCharacter::ApplyAbilityWithLocation(FVector Location)
{
	auto Character = Cast<ACharacter>(GetOuter());
	if (Character)
	{
		Character->SetActorLocation(Location);
	}
}

void UTPSGrenadeMoveCharacter::CancelAbility()
{
	GetOwnerEventComponent()->OnSpAttackHitEvent.Remove(DelegateHandle);
}

void UTPSGrenadeMoveCharacter::InitializeAbilityEvent()
{
	DelegateHandle = GetOwnerEventComponent()->OnSpAttackHitEvent.AddUObject(this, &UTPSGrenadeMoveCharacter::ApplyAbilityWithLocation);

}
