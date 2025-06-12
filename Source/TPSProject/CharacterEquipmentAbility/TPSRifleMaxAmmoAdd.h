// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSRifleMaxAmmoAdd.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSRifleMaxAmmoAdd : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()

public:
	UTPSRifleMaxAmmoAdd();

	virtual void InitializeWeaponAbility(UTPSGameplayEventSystem* InitEventSystem, FWeaponContext& WeaponContext) override;
};
