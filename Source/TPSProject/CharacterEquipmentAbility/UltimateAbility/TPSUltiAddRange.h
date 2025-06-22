// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSUltiAddRange.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSUltiAddRange : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
public:
	UTPSUltiAddRange();

	virtual void InitializeUltimateAbility(FUltimateSkillContext& SkillContext) override;
};
