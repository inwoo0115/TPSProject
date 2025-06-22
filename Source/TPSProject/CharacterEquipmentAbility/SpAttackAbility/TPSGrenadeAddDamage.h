// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSGrenadeAddDamage.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSGrenadeAddDamage : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
	
public:
	UTPSGrenadeAddDamage();

	virtual void InitializeSpAttackAbility(FSpAttackSkillContext& SkillContext) override;
};
