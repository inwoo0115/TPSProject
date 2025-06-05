// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSWeaponBase.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"


void ATPSWeaponBase::AddAbility(UTPSEquipmentAbilityBase* NewAbility)
{
	if (NewAbility)
	{
		AbilitySlot.Add(NewAbility);
	}
}

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

