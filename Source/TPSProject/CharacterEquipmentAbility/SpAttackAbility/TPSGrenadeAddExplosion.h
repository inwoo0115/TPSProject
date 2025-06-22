// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSGrenadeAddExplosion.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSGrenadeAddExplosion : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
public:
	UTPSGrenadeAddExplosion();

	virtual void InitializeSpAttackAbility(FSpAttackSkillContext& SkillContext) override;
	virtual void ApplyAbilityWithLocation(FVector Location);
	virtual void CancelAbility() override;
	virtual void InitializeAbilityEvent() override;

protected:
	UPROPERTY()
	TObjectPtr<class UNiagaraSystem> ExplosionEffect;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCApplyAbility(FVector Location);
};
