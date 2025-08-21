// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/DroneAbility/TPSDroneChangeAttackDrone.h"
#include "TPSDroneChangeAttackDrone.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"

UTPSDroneChangeAttackDrone::UTPSDroneChangeAttackDrone()
{
	AbilityName = FText::FromString(TEXT("Attack Drone"));

	AbilityDescription = FText::FromString(TEXT("Drone is Attacking"));

	AbilityType = EAbilityType::DroneAbility;
}

void UTPSDroneChangeAttackDrone::InitializeDroneAbility(FDroneSkillContext& SkillContext)
{
	Super::InitializeDroneAbility(SkillContext);

	SkillContext.Power -= 20.0f;
	SkillContext.CurrentDroneActor = EDroneType::AttackDrone;
}
