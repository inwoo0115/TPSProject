// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSWeaponComponent.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "TPSGameplayEventSystem.h"

void UTPSWeaponComponent::EquipWeapon(TSubclassOf<ATPSWeaponBase> WeaponClass)
{
	if (EquippedWeapon)
	{
		EquippedWeapon->Destroy();
	}

	UWorld* World = GetWorld();
	if (World && WeaponClass)
	{
		//EquippedWeapon = World->SpawnActor<ATPSWeaponBase>(WeaponClass);
		// 컴포넌트 오너의 메쉬 설정 TODO
	}
}

void UTPSWeaponComponent::Initialize(UTPSGameplayEventSystem* InputEventSystem)
{
	EventSystem = InputEventSystem;
}

