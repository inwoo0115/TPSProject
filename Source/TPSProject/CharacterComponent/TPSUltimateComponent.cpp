// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSUltimateComponent.h"
#include "CharacterEquipment/TPSUltimateSkillBase.h"
#include "GameFramework/Character.h"

void UTPSUltimateComponent::ShowCastUI()
{
    auto UltiEquipment = Cast<ATPSUltimateSkillBase>(Equipment);
    if (UltiEquipment)
    {
        UltiEquipment->ShowUI();
    }
}

void UTPSUltimateComponent::CastSkill()
{
    auto UltiEquipment = Cast<ATPSUltimateSkillBase>(Equipment);
    if (UltiEquipment)
    {
        UltiEquipment->CastSkill();
    }
}

void UTPSUltimateComponent::LaunchSkill()
{
    auto UltiEquipment = Cast<ATPSUltimateSkillBase>(Equipment);
    if (UltiEquipment)
    {
        UltiEquipment->LaunchSkill();
    }
}

bool UTPSUltimateComponent::GetCanCastSkill()
{
    auto UltiEquipment = Cast<ATPSUltimateSkillBase>(Equipment);
    if (UltiEquipment)
    {
        return UltiEquipment->GetCanCast();
    }

    return false;
}

void UTPSUltimateComponent::DeleteUI()
{
	auto UltiEquipment = Cast<ATPSUltimateSkillBase>(Equipment);
	if (UltiEquipment)
	{
		UltiEquipment->DeleteTargetUI();
	}
}

bool UTPSUltimateComponent::IsInRange()
{
	auto UltiEquipment = Cast<ATPSUltimateSkillBase>(Equipment);
	if (UltiEquipment)
	{
		return UltiEquipment->GetInRange();
	}

	return false;
}
