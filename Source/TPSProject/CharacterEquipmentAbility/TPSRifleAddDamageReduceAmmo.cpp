// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleAddDamageReduceAmmo.h"
#include "CharacterComponent/TPSWeaponComponent.h"

void UTPSRifleAddDamageReduceAmmo::InitializeAbility(UActorComponent* InitializeComponent)
{
	UTPSWeaponComponent* WeaponComponent = Cast<UTPSWeaponComponent>(InitializeComponent);
	if (WeaponComponent)
	{
		WeaponComponent->EquippedWeapon->MaxAmmo -= 10;
		WeaponComponent->EquippedWeapon->Damage += 20.0f;
		CachedComponent = WeaponComponent;
	}
}
