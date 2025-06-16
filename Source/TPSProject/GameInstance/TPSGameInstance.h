// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"
#include "CharacterEquipment/TPSSpAttackSkillBase.h"
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
	TSubclassOf<ATPSWeaponBase> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ATPSDroneSkillBase> DroneSkillEquipmentClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ATPSSpAttackSkillBase> SpAttackSkillEquipmentClass;
};
