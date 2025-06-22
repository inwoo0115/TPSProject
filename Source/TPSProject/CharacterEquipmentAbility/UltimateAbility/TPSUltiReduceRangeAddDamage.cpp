// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/UltimateAbility/TPSUltiReduceRangeAddDamage.h"
#include "CharacterEquipment/TPSUltimateSkillBase.h"

UTPSUltiReduceRangeAddDamage::UTPSUltiReduceRangeAddDamage()
{
	AbilityName = FText::FromString(TEXT("Concentrate"));
	AbilityDescription = FText::FromString(TEXT("Reduce Range and Add Damage"));
}

void UTPSUltiReduceRangeAddDamage::InitializeUltimateAbility(FUltimateSkillContext& SkillContext)
{
	Super::InitializeUltimateAbility(SkillContext);

	SkillContext.AttackRadius -= 200.0f;
	SkillContext.Damage += 20;
}
