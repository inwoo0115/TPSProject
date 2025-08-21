// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/DroneAbility/TPSDroneMoreLifeTime.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"

UTPSDroneMoreLifeTime::UTPSDroneMoreLifeTime()
{
	AbilityName = FText::FromString(TEXT("More LifeTime"));

	AbilityDescription = FText::FromString(TEXT("Add 5 seconde to Drone Lifetime"));

	AbilityType = EAbilityType::DroneAbility;
}

void UTPSDroneMoreLifeTime::InitializeDroneAbility(FDroneSkillContext& SkillContext)
{
	Super::InitializeDroneAbility(SkillContext);

	SkillContext.LifeTime += 5.0f;
}
