// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleAddLaserBullet.h"
#include "CharacterComponent/TPSWeaponComponent.h"
#include "CharacterEquipment/TPSBasicRifle.h"

void UTPSRifleAddLaserBullet::InitializeAbility(UActorComponent* InitializeComponent)
{
	UTPSWeaponComponent* WeaponComponent = Cast<UTPSWeaponComponent>(InitializeComponent);
	if (WeaponComponent)
	{
		auto Weapon = Cast<ATPSBasicRifle>(WeaponComponent->EquippedWeapon);
		if (Weapon)
		{
			Weapon->HasLaserMode = true;
		}
		CachedComponent = WeaponComponent;
	}
}

void UTPSRifleAddLaserBullet::ApplyAbility()
{
}
