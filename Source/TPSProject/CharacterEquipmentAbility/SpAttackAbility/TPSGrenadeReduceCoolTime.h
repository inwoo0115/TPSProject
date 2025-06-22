// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSGrenadeReduceCoolTime.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSGrenadeReduceCoolTime : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
	
public:
	UTPSGrenadeReduceCoolTime();

	virtual void InitializeSpAttackAbility(FSpAttackSkillContext& SkillContext) override;
};
