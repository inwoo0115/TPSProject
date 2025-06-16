// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterEquipmentAbility/TPSAbilityType.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSSpAttackSkillData.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSSpAttackSkillData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = EquipmentAbility)
	TMap<EAbilityType, TSubclassOf<UTPSEquipmentAbilityBase>> AbilityList;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	float Damage;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	float CoolTime;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	float UltiGaugeRatio;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	TSoftObjectPtr<UTexture2D> SkillEquipmentIcon;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	FText SkillEquipmentName;
};
