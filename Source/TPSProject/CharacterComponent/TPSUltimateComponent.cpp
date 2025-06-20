// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSUltimateComponent.h"
#include "CharacterEquipment/TPSUltimateSkillBase.h"

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
