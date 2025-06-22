// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSUltiReduceRangeAddDamage.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSUltiReduceRangeAddDamage : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
public:
	UTPSUltiReduceRangeAddDamage();

	virtual void InitializeUltimateAbility(FUltimateSkillContext& SkillContext) override;
};
