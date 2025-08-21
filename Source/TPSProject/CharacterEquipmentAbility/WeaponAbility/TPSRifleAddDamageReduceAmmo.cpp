// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSRifleAddDamageReduceAmmo.h"
#include "CharacterEquipment/TPSWeaponBase.h"

UTPSRifleAddDamageReduceAmmo::UTPSRifleAddDamageReduceAmmo()
{
	AbilityName = FText::FromString(TEXT("Selection and Concentration"));

	AbilityDescription = FText::FromString(TEXT("Damage Boost 30% and Lose 10 Ammo"));

	AbilityType = EAbilityType::WeaponAbility;
}

void UTPSRifleAddDamageReduceAmmo::InitializeWeaponAbility(FWeaponContext& WeaponContext)
{
	Super::InitializeWeaponAbility(WeaponContext);

	WeaponContext.MaxAmmo -= 10;
	WeaponContext.CurrentAmmo -= 10;
	WeaponContext.Damage += 20.0f;
}
