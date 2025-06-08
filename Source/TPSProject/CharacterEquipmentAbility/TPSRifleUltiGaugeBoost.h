// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSRifleUltiGaugeBoost.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSRifleUltiGaugeBoost : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()

public:
	virtual void InitializeAbility(UActorComponent* InitializeComponent) override;

protected:
	TObjectPtr<class UTPSWeaponComponent> CachedComponent;
};
