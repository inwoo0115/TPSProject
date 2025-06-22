// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSDroneAddPower.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSDroneAddPower : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
	
public:
	UTPSDroneAddPower();

	virtual void InitializeDroneAbility(FDroneSkillContext& SkillContext) override;

};
