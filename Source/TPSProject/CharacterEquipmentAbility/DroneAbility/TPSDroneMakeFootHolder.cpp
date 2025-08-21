// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/DroneAbility/TPSDroneMakeFootHolder.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"
#include "Summons/TPSDroneType.h"

UTPSDroneMakeFootHolder::UTPSDroneMakeFootHolder()
{
	AbilityName = FText::FromString(TEXT("Foot Holder"));

	AbilityDescription = FText::FromString(TEXT("You can walk over Drone!"));

	AbilityType = EAbilityType::DroneAbility;
}

void UTPSDroneMakeFootHolder::InitializeDroneAbility(FDroneSkillContext& SkillContext)
{
	Super::InitializeDroneAbility(SkillContext);

	SkillContext.CurrentDroneActor = EDroneType::FootHolderDrone;
}
