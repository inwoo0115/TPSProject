// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterEquipmentAbility/TPSAbilityType.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "Summons/TPSUltimateType.h"
#include "Summons/TPSUltimateActorBase.h"
#include "Summons/TPSSkillRangeDecalBase.h"
#include "TPSUltimateSkillData.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSUltimateSkillData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = EquipmentAbility)
	TMap<EAbilityType, TSubclassOf<UTPSEquipmentAbilityBase>> AbilityList;

	UPROPERTY(EditAnywhere, Category = UltimateList)
	TMap<EUltimateType, TSubclassOf<ATPSUltimateActorBase>> UltimateActorList;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	float Damage;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	float LifeTime;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	float UltiGauge;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	float AttackTimes;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	float AttackRadius;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	TSoftObjectPtr<UTexture2D> SkillEquipmentIcon;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	FText SkillEquipmentName;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	TSubclassOf<ATPSSkillRangeDecalBase> RangeDecal;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	EUltimateType CurrentUltimate;
};
