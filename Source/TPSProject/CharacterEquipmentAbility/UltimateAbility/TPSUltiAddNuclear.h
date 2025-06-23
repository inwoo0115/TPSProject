// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSUltiAddNuclear.generated.h"

class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSUltiAddNuclear : public UTPSEquipmentAbilityBase
{
	GENERATED_BODY()
	

public:
	UTPSUltiAddNuclear();

	virtual void InitializeUltimateAbility(FUltimateSkillContext& SkillContext) override;
	virtual void ApplyAbilityWithLocation(FVector Location);
	virtual void CancelAbility() override;
	virtual void InitializeAbilityEvent() override;

	void ApplyNuclearDamage(FVector Location);

protected:
	UPROPERTY()
	TObjectPtr<class UNiagaraSystem> ExplosionEffect;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCApplyAbility(FVector Location);

	UFUNCTION(Server, Reliable)
	void ServerRPCApplyAbility(FVector Location);
};
