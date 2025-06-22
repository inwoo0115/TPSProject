// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSRifleDroneCoolDown.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"

UTPSRifleDroneCoolDown::UTPSRifleDroneCoolDown()
{
	AbilityName = FText::FromString(TEXT("More Droner"));
	AbilityDescription = FText::FromString(TEXT("Cooldown Drone Skill when attack"));
}

void UTPSRifleDroneCoolDown::InitializeWeaponAbility(FWeaponContext& WeaponContext)
{
	Super::InitializeWeaponAbility(WeaponContext);

}

void UTPSRifleDroneCoolDown::ApplyAbility()
{
	GetOwnerEventComponent()->OnDroneFieldChangeEvent.Broadcast(FName(TEXT("CurrentCoolTime")), 1.0f);
}

void UTPSRifleDroneCoolDown::CancelAbility()
{
	GetOwnerEventComponent()->OnAttackHitEvent.Remove(DelegateHandle);
}

void UTPSRifleDroneCoolDown::InitializeAbilityEvent()
{
	DelegateHandle = GetOwnerEventComponent()->OnAttackHitEvent.AddUObject(this, &UTPSRifleDroneCoolDown::ApplyAbility);
}
