// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSDroneBoostHeal.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSDroneBoostHeal : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
public:
	UTPSDroneBoostHeal();

	virtual void InitializeDroneAbility(FDroneSkillContext& SkillContext) override;
};
