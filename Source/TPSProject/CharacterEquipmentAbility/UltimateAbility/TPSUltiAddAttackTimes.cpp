// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/UltimateAbility/TPSUltiAddAttackTimes.h"
#include "CharacterEquipment/TPSUltimateSkillBase.h"


UTPSUltiAddAttackTimes::UTPSUltiAddAttackTimes()
{
	AbilityName = FText::FromString(TEXT("More Attack"));
	AbilityDescription = FText::FromString(TEXT("Add Additional 10 Ultimate Attacks"));

}

void UTPSUltiAddAttackTimes::InitializeUltimateAbility(FUltimateSkillContext& SkillContext)
{
	Super::InitializeUltimateAbility(SkillContext);

	SkillContext.AttackTimes += 10; // Add 10 additional attacks
}
