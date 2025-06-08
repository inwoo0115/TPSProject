// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleMaxAmmoAdd.h"
#include "CharacterComponent/TPSWeaponComponent.h"

void UTPSRifleMaxAmmoAdd::InitializeAbility(UActorComponent* InitializeComponent)
{
	UTPSWeaponComponent* WeaponComponent = Cast<UTPSWeaponComponent>(InitializeComponent);
	if (WeaponComponent)
	{
		WeaponComponent->EquippedWeapon->MaxAmmo += 10;
		CachedComponent = WeaponComponent;
	}
}
