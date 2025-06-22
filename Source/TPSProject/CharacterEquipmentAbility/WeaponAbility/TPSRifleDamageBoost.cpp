// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSRifleDamageBoost.h"
#include "CharacterEquipment/TPSWeaponBase.h"

UTPSRifleDamageBoost::UTPSRifleDamageBoost()
{
	AbilityName = FText::FromString(TEXT("More Power"));
	AbilityDescription = FText::FromString(TEXT("Damage Boost 20%"));
}

void UTPSRifleDamageBoost::InitializeWeaponAbility(FWeaponContext& WeaponContext)
{
	Super::InitializeWeaponAbility(WeaponContext);

	WeaponContext.Damage += 10.0f;
}
