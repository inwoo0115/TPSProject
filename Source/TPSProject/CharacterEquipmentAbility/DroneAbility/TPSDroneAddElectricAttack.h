// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSDroneAddElectricAttack.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSDroneAddElectricAttack : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
	
public:
	UTPSDroneAddElectricAttack();

	virtual void InitializeDroneAbility(FDroneSkillContext& SkillContext) override;
};
