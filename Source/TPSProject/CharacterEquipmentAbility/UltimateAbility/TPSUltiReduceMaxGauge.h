// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSUltiReduceMaxGauge.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSUltiReduceMaxGauge : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
public:
	UTPSUltiReduceMaxGauge();

	virtual void InitializeUltimateAbility(FUltimateSkillContext& SkillContext) override;
};
