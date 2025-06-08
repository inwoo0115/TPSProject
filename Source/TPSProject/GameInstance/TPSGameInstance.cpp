// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/TPSGameInstance.h"

void UTPSGameInstance::Init()
{
	Super::Init();
	
	// Weapon class 초기화
	TSoftClassPtr<ATPSWeaponBase> SoftClass_Main(FSoftClassPath(TEXT("/Script/TPSProject.TPSBasicRifle")));
	if (SoftClass_Main.IsValid())
	{
		WeaponClass = SoftClass_Main.LoadSynchronous();
	}

	// 머터리얼 초기화
	TSoftObjectPtr<UMaterialInterface> SoftMat(FSoftObjectPath(TEXT("/Game/ParagonWraith/Characters/Heroes/Wraith/Materials/M_Wraith_Gun.M_Wraith_Gun")));
	if (SoftMat.IsValid())
	{
		WeaponMaterial = SoftMat.LoadSynchronous();
	}
}
