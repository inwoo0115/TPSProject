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

void UTPSRifleAddLaserBullet::InitializeAbility(UTPSGameplayEventSystem* InitEventSystem, FWeaponContext& WeaponContext)
{
	Super::InitializeAbility(InitEventSystem, WeaponContext);

	WeaponContext.AttackRatio = 0.9f;
	WeaponContext.CurrentBullet = EProjectileType::RifleLaser;
	WeaponContext.Damage += 50.0f;
	WeaponContext.RequireAmmo = 10;
}
