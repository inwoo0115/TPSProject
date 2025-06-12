// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleMaxAmmoAdd.h"
#include "CharacterComponent/TPSWeaponComponent.h"

UTPSRifleMaxAmmoAdd::UTPSRifleMaxAmmoAdd()
{
	AbilityName = FText::FromString(TEXT("I Can do this All Day"));
	AbilityDescription = FText::FromString(TEXT("Add 50 Ammo"));
}

void UTPSRifleMaxAmmoAdd::InitializeAbility(UTPSGameplayEventSystem* InitEventSystem, FWeaponContext& WeaponContext)
{
	Super::InitializeAbility(InitEventSystem, WeaponContext);

	WeaponContext.MaxAmmo += 50;
	WeaponContext.CurrentAmmo += 50;
}
