// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSGrenadeAddBulletDamage.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSGrenadeAddBulletDamage : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
	
public:
	UTPSGrenadeAddBulletDamage();

	virtual void InitializeSpAttackAbility(FSpAttackSkillContext& SkillContext) override;
	virtual void ApplyAbilityWithLocation(FVector Location);
	virtual void CancelAbility() override;
	virtual void InitializeAbilityEvent() override;
};
