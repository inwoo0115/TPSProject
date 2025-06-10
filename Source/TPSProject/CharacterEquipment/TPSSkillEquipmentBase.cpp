// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSSkillEquipmentBase.h"

// Sets default values
ATPSSkillEquipmentBase::ATPSSkillEquipmentBase()
{
	// 루트 컴포넌트 생성 
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void ATPSSkillEquipmentBase::Cast()
{
}

void ATPSSkillEquipmentBase::Effect()
{
}

void ATPSSkillEquipmentBase::ClearAbilitySlot()
{
	AbilitySlot.Empty();
}

void ATPSSkillEquipmentBase::InitializeAbilities()
{
	for (UTPSEquipmentAbilityBase* Ability : AbilitySlot)
	{
		if (Ability && OwnerComponent)
		{
			Ability->InitializeAbility(OwnerComponent);
		}
	}
}

void ATPSSkillEquipmentBase::InitializeComponent(UActorComponent* NewComponent)
{
	OwnerComponent = NewComponent;
}

void ATPSSkillEquipmentBase::InitializeAbilitiesFromDataAsset(EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
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

UActorComponent* ATPSSkillEquipmentBase::GetOwnerComponent() const
{
	return OwnerComponent;
}
