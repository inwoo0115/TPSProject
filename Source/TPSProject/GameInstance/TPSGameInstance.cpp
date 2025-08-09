// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/TPSGameInstance.h"

void UTPSGameInstance::Init()
{
	Super::Init();
	
	// 캐릭터가 가지고 있는 Equipment class
	TSoftClassPtr<ATPSWeaponBase> SoftClass_Weapon1(FSoftClassPath(TEXT("/Script/TPSProject.TPSBasicRifle")));
	if (SoftClass_Weapon1.IsValid())
	{
		WeaponClass1 = SoftClass_Weapon1.LoadSynchronous();
	}

	TSoftClassPtr<ATPSWeaponBase> SoftClass_Weapon2(FSoftClassPath(TEXT("/Script/TPSProject.TPSFlameRifle")));
	if (SoftClass_Weapon2.IsValid())
	{
		WeaponClass2 = SoftClass_Weapon2.LoadSynchronous();
	}

	TSoftClassPtr<ATPSSpAttackSkillBase> SoftClass_SpAttack(FSoftClassPath(TEXT("/Script/TPSProject.TPSBasicGrenade")));
	if (SoftClass_SpAttack.IsValid())
	{
		SpAttackSkillEquipmentClass = SoftClass_SpAttack.LoadSynchronous();
	}

	TSoftClassPtr<ATPSDroneSkillBase> SoftClass_Drone(FSoftClassPath(TEXT("/Script/TPSProject.TPSBasicDrone")));
	if (SoftClass_Drone.IsValid())
	{
		DroneSkillEquipmentClass = SoftClass_Drone.LoadSynchronous();
	}

	TSoftClassPtr<ATPSUltimateSkillBase> SoftClass_Ulti(FSoftClassPath(TEXT("/Script/TPSProject.TPSBasicUltimate")));
	if (SoftClass_Ulti.IsValid())
	{
		UltimateSkillEquipmentClass = SoftClass_Ulti.LoadSynchronous();
	}

	// 인벤토리 데이터 로드
	// LoadInventoryData();
}
