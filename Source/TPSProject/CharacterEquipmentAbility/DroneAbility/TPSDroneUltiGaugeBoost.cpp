// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/DroneAbility/TPSDroneUltiGaugeBoost.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"

UTPSDroneUltiGaugeBoost::UTPSDroneUltiGaugeBoost()
{
	AbilityName = FText::FromString(TEXT("UltiGauge Boost"));

	AbilityDescription = FText::FromString(TEXT("More Ulti Gauge by Drone"));
}

void UTPSDroneUltiGaugeBoost::InitializeDroneAbility(FDroneSkillContext& SkillContext)
{
	Super::InitializeDroneAbility(SkillContext);

	SkillContext.UltiGaugeRatio += 1.0;
}
