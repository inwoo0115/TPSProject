// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSSpAttackSkillComponent.h"
#include "CharacterEquipment/TPSSpAttackSkillBase.h"

void UTPSSpAttackSkillComponent::CastSkill()
{
	auto SkillEquipment = Cast<ATPSSpAttackSkillBase>(Equipment);
	if (SkillEquipment)
	{
		SkillEquipment->CastSkill();
	}
}

void UTPSSpAttackSkillComponent::LaunchSkill()
{
	auto SkillEquipment = Cast<ATPSSpAttackSkillBase>(Equipment);
	if (SkillEquipment)
	{
		SkillEquipment->LaunchSkill();
	}
}

void UTPSSpAttackSkillComponent::ShowCastUI()
{
	auto SkillEquipment = Cast<ATPSSpAttackSkillBase>(Equipment);
	if (SkillEquipment)
	{
		SkillEquipment->ShowUI();
	}
}


bool UTPSSpAttackSkillComponent::GetCanCastSkill()
{
	auto SkillEquipment = Cast<ATPSSpAttackSkillBase>(Equipment);
	if (SkillEquipment)
	{
		return SkillEquipment->GetCanCast();
	}

	return false;
}

void UTPSSpAttackSkillComponent::InitEquipmentAbilityList()
{
	auto SkillEquipment = Cast<ATPSSpAttackSkillBase>(Equipment);
	if (SkillEquipment)
	{
		SkillEquipment->InitializeAbilityListFromInventory();
	}
}
