// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/SpAttackAbility/TPSGrenadeReduceCoolTime.h"
#include "CharacterEquipment/TPSSpAttackSkillBase.h"

UTPSGrenadeReduceCoolTime::UTPSGrenadeReduceCoolTime()
{
	AbilityName = FText::FromString(TEXT("Reduce Cool Time"));
	AbilityDescription = FText::FromString(TEXT("Reduce Cool Time -3.0 second"));

	AbilityType = EAbilityType::SpAttackAbility;
}

void UTPSGrenadeReduceCoolTime::InitializeSpAttackAbility(FSpAttackSkillContext& SkillContext)
{
	Super::InitializeSpAttackAbility(SkillContext);

	SkillContext.CoolTime -= 3.0f; // Reduce Cool Time by 3 seconds
}
