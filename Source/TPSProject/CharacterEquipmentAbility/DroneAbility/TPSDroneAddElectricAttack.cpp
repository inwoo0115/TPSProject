// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/DroneAbility/TPSDroneAddElectricAttack.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"
#include "Summons/TPSDroneType.h"

UTPSDroneAddElectricAttack::UTPSDroneAddElectricAttack()
{
	AbilityName = FText::FromString(TEXT("Electric Shock"));

	AbilityDescription = FText::FromString(TEXT("Spawn Electric Shock near Ground"));
}

void UTPSDroneAddElectricAttack::InitializeDroneAbility(FDroneSkillContext& SkillContext)
{
	Super::InitializeDroneAbility(SkillContext);

	SkillContext.CurrentDroneActor = EDroneType::ElectricDrone;
}
