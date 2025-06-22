// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSDroneMoreLifeTime.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSDroneMoreLifeTime : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()

public:
	UTPSDroneMoreLifeTime();

	virtual void InitializeDroneAbility(FDroneSkillContext& SkillContext) override;
	
};
