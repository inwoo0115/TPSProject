// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"
#include "CharacterEquipment/TPSSpAttackSkillBase.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "CharacterEquipment/TPSUltimateSkillBase.h"
#include "TPSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ATPSWeaponBase> WeaponClass1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ATPSWeaponBase> WeaponClass2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ATPSDroneSkillBase> DroneSkillEquipmentClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ATPSSpAttackSkillBase> SpAttackSkillEquipmentClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ATPSUltimateSkillBase> UltimateSkillEquipmentClass;
};
