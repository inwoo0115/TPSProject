// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSUltiLightning.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSUltiLightning : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
public:
	UTPSUltiLightning();

	virtual void InitializeUltimateAbility(FUltimateSkillContext& SkillContext) override;
};
