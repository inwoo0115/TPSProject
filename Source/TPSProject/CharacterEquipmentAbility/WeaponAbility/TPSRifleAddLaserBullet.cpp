// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSRifleAddLaserBullet.h"
#include "Projectile/TPSProjectileType.h"
#include "CharacterEquipment/TPSWeaponBase.h"

UTPSRifleAddLaserBullet::UTPSRifleAddLaserBullet()
{
	AbilityName = FText::FromString(TEXT("LaserMode"));
	AbilityDescription = FText::FromString(TEXT("Change to Laser Bullet when Attack"));
}

void UTPSRifleAddLaserBullet::InitializeWeaponAbility(FWeaponContext& WeaponContext)
{
	Super::InitializeWeaponAbility(WeaponContext);

	WeaponContext.AttackRatio = 0.9f;
	WeaponContext.CurrentBullet = EProjectileType::RifleLaser;
	WeaponContext.Damage += 50.0f;
	WeaponContext.RequireAmmo = 10;
}
