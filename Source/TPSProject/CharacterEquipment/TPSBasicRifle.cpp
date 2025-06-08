// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSBasicRifle.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityData.h"
#include "Projectile/TPSProjectileListData.h"

ATPSBasicRifle::ATPSBasicRifle()
{
	static ConstructorHelpers::FObjectFinder<UTPSEquipmentAbilityData> AbilityDataRef(TEXT("/Game/TPSProject/EquipmentAbility/BasicRifleAbility.BasicRifleAbility"));
	if (AbilityDataRef.Object)
	{
		AbilityData = AbilityDataRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTPSProjectileListData> ListDataRef(TEXT("/Game/TPSProject/ProjectileList/BasicRifleProjectiles.BasicRifleProjectiles"));
	if (ListDataRef.Object)
	{
		Projectiles = ListDataRef.Object;
	}

	// 데이터 에셋에서 특성 초기화
	InitializeAbilitiesFromDataAsset();
}

void ATPSBasicRifle::Fire()
{
}

void ATPSBasicRifle::Reload()
{
}
