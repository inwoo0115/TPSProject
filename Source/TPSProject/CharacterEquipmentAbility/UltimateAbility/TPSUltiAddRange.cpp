// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/UltimateAbility/TPSUltiAddRange.h"
#include "CharacterEquipment/TPSUltimateSkillBase.h"

UTPSUltiAddRange::UTPSUltiAddRange()
{
	AbilityName = FText::FromString(TEXT("More Range"));
	AbilityDescription = FText::FromString(TEXT("Add Additional Ultimate Range"));
}

void UTPSUltiAddRange::InitializeUltimateAbility(FUltimateSkillContext& SkillContext)
{
	Super::InitializeUltimateAbility(SkillContext);

	SkillContext.AttackRadius += 500.0f; // Add 500 units to the attack range
}
