// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSSkillComponentBase.h"
#include "CharacterEquipment/TPSSkillEquipmentBase.h"
#include "TPSGameplayEventSystem.h"


void UTPSSkillComponentBase::Equip(TSubclassOf<ATPSSkillEquipmentBase> EquipmentClass)
{
	if (Equipment)
	{
		Equipment->Destroy();
	}
	UWorld* World = GetWorld();
	if (World && EquipmentClass)
	{
		Equipment = World->SpawnActor<ATPSSkillEquipmentBase>(EquipmentClass);

		Equipment->InitializeComponent(this);
		Equipment->InitializeAbilitiesFromDataAsset(EAbilityType::Group1Ability1, EAbilityType::Group2Ability1, EAbilityType::Group3Ability1);
		Equipment->InitializeAbilities();
	}
}

void UTPSSkillComponentBase::CastSkill()
{
	Equipment->Cast();
}

void UTPSSkillComponentBase::EffectSkill()
{
	Equipment->Effect();
}

void UTPSSkillComponentBase::Initialize(UTPSGameplayEventSystem* InputEventSystem)
{
	EventSystem = InputEventSystem;
}
