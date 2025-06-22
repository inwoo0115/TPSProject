// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSDroneMoveToGrenade.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSDroneMoveToGrenade : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
	
public:
	UTPSDroneMoveToGrenade();

	virtual void InitializeDroneAbility(FDroneSkillContext& SkillContext) override;
	virtual void ApplyAbility() override;
	virtual void CancelAbility() override;
	virtual void InitializeAbilityEvent() override;
};
