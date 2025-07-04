// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSRifleDroneCoolDown.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSRifleDroneCoolDown : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()

public:
	UTPSRifleDroneCoolDown();

	virtual void InitializeWeaponAbility(FWeaponContext& WeaponContext) override;
	virtual void ApplyAbilityWithLocation(FVector Location);

	virtual void CancelAbility() override;
	virtual void InitializeAbilityEvent() override;
};
