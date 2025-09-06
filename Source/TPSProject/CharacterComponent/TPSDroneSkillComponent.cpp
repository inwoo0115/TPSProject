// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSDroneSkillComponent.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"

void UTPSDroneSkillComponent::ShowCastUI()
{
	auto SkillEquipment = Cast<ATPSDroneSkillBase>(Equipment);
	if (SkillEquipment)
	{
		SkillEquipment->ShowUI();
	}
}

void UTPSDroneSkillComponent::CastSkill()
{
	auto SkillEquipment = Cast<ATPSDroneSkillBase>(Equipment);
	if (SkillEquipment)
	{
		SkillEquipment->CastSkill();
	}
}

void UTPSDroneSkillComponent::LaunchSkill()
{
	auto SkillEquipment = Cast<ATPSDroneSkillBase>(Equipment);
	if (SkillEquipment)
	{
		SkillEquipment->LaunchSkill();
	}
}

bool UTPSDroneSkillComponent::GetCanCastSkill()
{
	auto SkillEquipment = Cast<ATPSDroneSkillBase>(Equipment);
	if (SkillEquipment)
	{
		return SkillEquipment->GetCanCast();
	}
	return false;
}

void UTPSDroneSkillComponent::InitEquipmentAbilityList()
{
	auto SkillEquipment = Cast<ATPSDroneSkillBase>(Equipment);
	if (SkillEquipment)
	{
		SkillEquipment->InitializeAbilityListFromInventory();
	}
}
