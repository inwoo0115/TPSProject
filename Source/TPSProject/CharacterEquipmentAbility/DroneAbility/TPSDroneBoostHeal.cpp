// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/DroneAbility/TPSDroneBoostHeal.h"
#include "TPSDroneBoostHeal.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"

UTPSDroneBoostHeal::UTPSDroneBoostHeal()
{
	AbilityName = FText::FromString(TEXT("More Heal"));

	AbilityDescription = FText::FromString(TEXT("Add 10 Heal per Seconds"));
}

void UTPSDroneBoostHeal::InitializeDroneAbility(FDroneSkillContext& SkillContext)
{
	Super::InitializeDroneAbility(SkillContext);

	SkillContext.Power += 10.0f;
}
