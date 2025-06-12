// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TPSEquipmentAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSEquipmentAbilityBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void InitializeWeaponAbility(UTPSGameplayEventSystem* InitEventSystem, FWeaponContext& WeaponContext);

	//virtual void InitializeGrenadeAbility(UTPSGameplayEventSystem* InitEventSystem, FSkillContext& SkillContext);

	//virtual void InitializeDroneAbility(UTPSGameplayEventSystem* InitEventSystem, FSkillContext& SkillContext);


	UFUNCTION()
	virtual void ApplyAbility();

	FText AbilityName;

	FText AbilityDescription;

protected:
	TObjectPtr<class UTPSGameplayEventSystem> EventSystem;
};
