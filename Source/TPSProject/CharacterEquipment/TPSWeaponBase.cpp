// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSWeaponBase.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityData.h"


void ATPSWeaponBase::ClearAbilitySlot()
{
	AbilitySlot.Empty();
}

void ATPSWeaponBase::InitializeAbilities()
{
	for (UTPSEquipmentAbilityBase* Ability : AbilitySlot)
	{
		if (Ability)
		{
			Ability->InitializeAbility(OwnerComponent);
		}
	}
}

void ATPSWeaponBase::InitializeComponent(UActorComponent* InitializeComponent)
{
	OwnerComponent = InitializeComponent;
}

void ATPSWeaponBase::InitializeAbilitiesFromDataAsset()
{
	if (!AbilityData) return;

	// TODO : 일단 다 가져오는데 나중에 특정 Ability만 가져오도록 수정 필요
	for (const TSubclassOf<UTPSEquipmentAbilityBase>& AbilityClass : AbilityData->EquipmentAbilitys)
	{
		if (AbilityClass)
		{
			UTPSEquipmentAbilityBase* NewAbility = NewObject<UTPSEquipmentAbilityBase>();
			AbilitySlot.Add(NewAbility);
		}
	}
}

void ATPSWeaponBase::Fire()
{
}

void ATPSWeaponBase::Release()
{
}

void ATPSWeaponBase::Reload()
{
}