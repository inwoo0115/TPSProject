// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterComponent/TPSSkillComponentBase.h"
#include "TPSUltimateComponent.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSUltimateComponent : public UTPSSkillComponentBase
{
	GENERATED_BODY()
	
public:
	// 장비장착
	virtual void Equip(TSubclassOf<ATPSAbilityEquipmentBase> EquipmentClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3) override;

	// 스킬 시전 범위 표시 
	void ShowCastUI();

	// 스킬 사용 
	virtual void CastSkill() override;

	// 스킬 입력 처리
	virtual void LaunchSkill() override;

	// 스킬 사용 가능 
	virtual bool GetCanCastSkill() override;

	// UI 제거
	virtual void DeleteUI();
};
