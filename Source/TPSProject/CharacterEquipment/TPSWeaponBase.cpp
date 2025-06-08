// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSWeaponBase.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityData.h"
#include "Projectile/TPSProjectileListData.h"
#include "Projectile/TPSProjectileBase.h"


ATPSWeaponBase::ATPSWeaponBase()
{
	// 루트 컴포넌트 생성 
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void ATPSWeaponBase::ClearAbilitySlot()
{
	AbilitySlot.Empty();
}

void ATPSWeaponBase::InitializeAbilities()
{
	for (UTPSEquipmentAbilityBase* Ability : AbilitySlot)
	{
		if (Ability && OwnerComponent)
		{
			Ability->InitializeAbility(OwnerComponent);
		}
	}
}

void ATPSWeaponBase::InitializeComponent(UActorComponent* NewComponent)
{
	OwnerComponent = NewComponent;
}

void ATPSWeaponBase::InitializeAbilitiesFromDataAsset(EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
	if (!AbilityData) return;
	// Ability1
	if (AbilityData->EquipmentAbilities.Contains(Ability1))
	{
		UTPSEquipmentAbilityBase* NewAbility1 = NewObject<UTPSEquipmentAbilityBase>(this, AbilityData->EquipmentAbilities[Ability1]);
		if (NewAbility1)
		{
			AbilitySlot.Add(NewAbility1);
		}
	}
	// Ability2
	if (AbilityData->EquipmentAbilities.Contains(Ability2))
	{
		UTPSEquipmentAbilityBase* NewAbility2 = NewObject<UTPSEquipmentAbilityBase>(this, AbilityData->EquipmentAbilities[Ability2]);
		if (NewAbility2)
		{
			AbilitySlot.Add(NewAbility2);
		}
	}
	// Ability3
	if (AbilityData->EquipmentAbilities.Contains(Ability3))
	{
		UTPSEquipmentAbilityBase* NewAbility3 = NewObject<UTPSEquipmentAbilityBase>(this, AbilityData->EquipmentAbilities[Ability3]);
		if (NewAbility3)
		{
			AbilitySlot.Add(NewAbility3);
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

UActorComponent* ATPSWeaponBase::GetOwnerComponent() const
{
	return OwnerComponent;
}