// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterEquipmentAbility/TPSAbilityType.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "Summons/TPSDroneType.h"
#include "Summons/TPSDroneActorBase.h"
#include "Summons/TPSSkillRangeDecalBase.h"
#include "TPSDroneSkillData.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSDroneSkillData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = DroneList)
	TMap<EDroneType, TSubclassOf<ATPSDroneActorBase>> DroneActorList;

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

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	EDroneType CurrentDroneActor;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	TSubclassOf<ATPSSkillRangeDecalBase> RangeDecal;
};
