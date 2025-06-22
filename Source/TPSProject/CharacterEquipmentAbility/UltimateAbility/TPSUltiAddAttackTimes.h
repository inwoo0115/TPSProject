// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSUltiAddAttackTimes.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSUltiAddAttackTimes : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
	
public:
	UTPSUltiAddAttackTimes();

	virtual void InitializeUltimateAbility(FUltimateSkillContext& SkillContext) override;
};
