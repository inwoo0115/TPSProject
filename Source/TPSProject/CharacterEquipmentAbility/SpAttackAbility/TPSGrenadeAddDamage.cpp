// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/SpAttackAbility/TPSGrenadeAddDamage.h"
#include "CharacterEquipment/TPSSpAttackSkillBase.h"

UTPSGrenadeAddDamage::UTPSGrenadeAddDamage()
{
	AbilityName = FText::FromString(TEXT("Add Damage"));
	AbilityDescription = FText::FromString(TEXT("Add More 10 Damage "));
}

void UTPSGrenadeAddDamage::InitializeSpAttackAbility(FSpAttackSkillContext& SkillContext)
{
	Super::InitializeSpAttackAbility(SkillContext);

	SkillContext.Damage += 10.0f; // Add 10 damage to the grenade attack
}
