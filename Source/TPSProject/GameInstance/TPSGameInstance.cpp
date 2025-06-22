// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/TPSGameInstance.h"

void UTPSGameInstance::Init()
{
	Super::Init();
	
	// 캐릭터가 가지고 있는 Equipment class
	TSoftClassPtr<ATPSWeaponBase> SoftClass_Main(FSoftClassPath(TEXT("/Script/TPSProject.TPSBasicRifle")));
	if (SoftClass_Main.IsValid())
	{
		WeaponClass = SoftClass_Main.LoadSynchronous();
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
}
