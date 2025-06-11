// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleAddLaserBullet.h"
#include "CharacterComponent/TPSWeaponComponent.h"
#include "CharacterEquipment/TPSBasicRifle.h"
#include "Projectile/TPSProjectileListData.h"

UTPSRifleAddLaserBullet::UTPSRifleAddLaserBullet()
{
	AbilityName = FText::FromString(TEXT("LaserMode"));
	AbilityDescription = FText::FromString(TEXT("Change to Laser Bullet when Attack"));
}

void UTPSRifleAddLaserBullet::InitializeAbility(UActorComponent* InitializeComponent)
{
	UTPSWeaponComponent* WeaponComponent = Cast<UTPSWeaponComponent>(InitializeComponent);
	if (WeaponComponent)
	{
		WeaponComponent->EquippedWeapon->AttackRatio = 0.9f;
		WeaponComponent->EquippedWeapon->CurrentBullet = EProjectileType::RifleLaser;
		WeaponComponent->EquippedWeapon->Damage += 50.0f;
		WeaponComponent->EquippedWeapon->RequireAmmo = 10;
		CachedComponent = WeaponComponent;
	}
}
