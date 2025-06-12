// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleDamageBoost.h"
#include "CharacterEquipment/TPSBasicRifle.h"
#include "CharacterComponent/TPSWeaponComponent.h"

UTPSRifleDamageBoost::UTPSRifleDamageBoost()
{
	AbilityName = FText::FromString(TEXT("More Power"));
	AbilityDescription = FText::FromString(TEXT("Damage Boost 20%"));
}

void UTPSRifleDamageBoost::InitializeAbility(UTPSGameplayEventSystem* InitEventSystem, FWeaponContext& WeaponContext)
{
	Super::InitializeAbility(InitEventSystem, WeaponContext);

	WeaponContext.Damage += 10.0f;
}
