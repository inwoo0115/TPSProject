// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSBasicRifle.h"
#include "CharacterEquipment/TPSWeaponData.h"

ATPSBasicRifle::ATPSBasicRifle()
{
	// Basic Rifle Data
	static ConstructorHelpers::FObjectFinder<UTPSWeaponData> WeaponDataRef(TEXT("/Game/TPSProject/EquipmentInfo/Weapon/BasicRifleData.BasicRifleData"));
	if (WeaponDataRef.Object)
	{
		WeaponData = WeaponDataRef.Object;
	}

	// 데이터 초기화
	SetWeaponContextFromData();
}
