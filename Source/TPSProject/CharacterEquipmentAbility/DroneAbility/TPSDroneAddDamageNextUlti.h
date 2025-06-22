// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSDroneAddDamageNextUlti.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSDroneAddDamageNextUlti : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
	
public:
	UTPSDroneAddDamageNextUlti();

	virtual void InitializeDroneAbility(FDroneSkillContext& SkillContext) override;
	virtual void ApplyAbilityWithLocation(FVector Location);
	virtual void CancelAbility() override;
	virtual void InitializeAbilityEvent() override;
};
