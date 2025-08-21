// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/UltimateAbility/TPSUltiLightning.h"
#include "CharacterEquipment/TPSUltimateSkillBase.h"
UTPSUltiLightning::UTPSUltiLightning()
{
	AbilityName = FText::FromString(TEXT("Thor : God of Thunder"));
	AbilityDescription = FText::FromString(TEXT("Change to Lightning Ultimate"));

	AbilityType = EAbilityType::UltimateAbility;
}

void UTPSUltiLightning::InitializeUltimateAbility(FUltimateSkillContext& SkillContext)
{
	Super::InitializeUltimateAbility(SkillContext);

	SkillContext.CurrentUltimate = EUltimateType::LightningUltimate;
}
