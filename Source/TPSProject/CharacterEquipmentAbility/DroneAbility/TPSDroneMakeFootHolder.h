// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSDroneMakeFootHolder.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSDroneMakeFootHolder : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
	
public:

	UTPSDroneMakeFootHolder();

	virtual void InitializeDroneAbility(FDroneSkillContext& SkillContext) override;
};
