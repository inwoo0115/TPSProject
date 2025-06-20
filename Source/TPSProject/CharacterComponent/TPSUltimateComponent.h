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
	// �������
	virtual void Equip(TSubclassOf<ATPSAbilityEquipmentBase> EquipmentClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3) override;

	// ��ų ���� ���� ǥ�� 
	void ShowCastUI();

	// ��ų ��� 
	virtual void CastSkill() override;

	// ��ų �Է� ó��
	virtual void LaunchSkill() override;

	// ��ų ��� ���� 
	virtual bool GetCanCastSkill() override;

	// UI ����
	virtual void DeleteUI();
};
