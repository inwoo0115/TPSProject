// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSDroneChangeAttackDrone.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSDroneChangeAttackDrone : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
public:
	UTPSDroneChangeAttackDrone();

	virtual void InitializeDroneAbility(FDroneSkillContext& SkillContext) override;
};
