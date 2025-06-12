// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "CharacterEquipment/TPSWeaponBase.h"

void UTPSEquipmentAbilityBase::InitializeWeaponAbility(UTPSGameplayEventSystem* InitEventSystem, FWeaponContext& WeaponContext)
{
	EventSystem = InitEventSystem;
}


void UTPSEquipmentAbilityBase::ApplyAbility()
{
}
