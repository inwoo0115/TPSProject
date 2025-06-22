// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/DroneAbility/TPSDroneAddPower.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"

UTPSDroneAddPower::UTPSDroneAddPower()
{
	AbilityName = FText::FromString(TEXT("More Power"));

	AbilityDescription = FText::FromString(TEXT("Add 10 Damage or Heal per second"));
}

void UTPSDroneAddPower::InitializeDroneAbility(FDroneSkillContext& SkillContext)
{
	Super::InitializeDroneAbility(SkillContext);

	SkillContext.Power += 10.0f;
}
