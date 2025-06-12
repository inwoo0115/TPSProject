// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleAddDamageReduceAmmo.h"
#include "CharacterEquipment/TPSWeaponBase.h"

UTPSRifleAddDamageReduceAmmo::UTPSRifleAddDamageReduceAmmo()
{
	AbilityName = FText::FromString(TEXT("Selection and Concentration"));

	AbilityDescription = FText::FromString(TEXT("Damage Boost 30% and Lose 10 Ammo"));
}

void UTPSRifleAddDamageReduceAmmo::InitializeWeaponAbility(UTPSGameplayEventSystem* InitEventSystem, FWeaponContext& WeaponContext)
{
	Super::InitializeWeaponAbility(InitEventSystem, WeaponContext);

	WeaponContext.MaxAmmo -= 10;
	WeaponContext.CurrentAmmo -= 10;
	WeaponContext.Damage += 20.0f;
}
