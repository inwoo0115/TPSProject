// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSRifleAddLaserBullet.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSRifleAddLaserBullet : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()

public:
	UTPSRifleAddLaserBullet();

	virtual void InitializeAbility(UActorComponent* InitializeComponent) override;
	virtual void ApplyAbility() override;

protected:
	TObjectPtr<class UTPSWeaponComponent> CachedComponent;
};
