// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSRifleAddDamageReduceAmmo.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSRifleAddDamageReduceAmmo : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
	
public:
	UTPSRifleAddDamageReduceAmmo();

	virtual void InitializeWeaponAbility(FWeaponContext& WeaponContext) override;

};
