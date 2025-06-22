// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/WeaponEquipment/TPSFlameRifle.h"
#include "TPSFlameRifle.h"

ATPSFlameRifle::ATPSFlameRifle()
{
	static ConstructorHelpers::FObjectFinder<UTPSWeaponData> WeaponDataRef(TEXT("/Game/TPSProject/EquipmentInfo/Weapon/FlameRifleData.FlameRifleData"));
	if (WeaponDataRef.Object)
	{
		WeaponData = WeaponDataRef.Object;
	}

	// ������ �ʱ�ȭ
	SetWeaponContextFromData();
}
