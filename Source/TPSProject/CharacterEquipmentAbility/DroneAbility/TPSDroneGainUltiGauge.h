// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSDroneGainUltiGauge.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSDroneGainUltiGauge : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
	
public:
	UTPSDroneGainUltiGauge();

	virtual void InitializeDroneAbility(FDroneSkillContext& SkillContext) override;
	virtual void ApplyAbility() override;
	virtual void CancelAbility() override;
	virtual void InitializeAbilityEvent() override;

	UFUNCTION(Server, Reliable)
	void ServerRPCApplyAbility();
};
