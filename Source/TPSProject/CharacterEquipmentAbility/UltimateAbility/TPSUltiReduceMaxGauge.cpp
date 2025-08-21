// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/UltimateAbility/TPSUltiReduceMaxGauge.h"
#include "CharacterEquipment/TPSUltimateSkillBase.h"
UTPSUltiReduceMaxGauge::UTPSUltiReduceMaxGauge()
{
	AbilityName = FText::FromString(TEXT("Reduce Max Gauge"));
	AbilityDescription = FText::FromString(TEXT("Reduce Max Gauge to 70%"));

	AbilityType = EAbilityType::UltimateAbility;
}

void UTPSUltiReduceMaxGauge::InitializeUltimateAbility(FUltimateSkillContext& SkillContext)
{
	Super::InitializeUltimateAbility(SkillContext);

	SkillContext.MaxGauge -= 30;
}
