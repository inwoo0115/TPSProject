// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSDroneUltiGaugeBoost.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSDroneUltiGaugeBoost : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()

public:
	UTPSDroneUltiGaugeBoost();

	virtual void InitializeDroneAbility(FDroneSkillContext& SkillContext) override;
};
