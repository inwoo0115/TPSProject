// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSRifleDamageBoost.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSRifleDamageBoost : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
	
public:
	UTPSRifleDamageBoost();

	virtual void InitializeWeaponAbility(FWeaponContext& WeaponContext) override;

};
