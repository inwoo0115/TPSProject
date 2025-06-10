// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSGameplayEventSystem.h"
#include "CharacterEquipment/TPSSkillEquipmentBase.h"
#include "TPSSkillComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UTPSSkillComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	// ��� ����
	virtual void Equip(TSubclassOf<ATPSSkillEquipmentBase> EquipmentClass);

	// ��ų ����
	virtual void CastSkill();

	// ��ų ����Ʈ
	virtual void EffectSkill();

	// �̺�Ʈ �ý��� ���
	void Initialize(UTPSGameplayEventSystem* InputEventSystem);

	UPROPERTY()
	TObjectPtr<class UTPSGameplayEventSystem> EventSystem;

	UPROPERTY()
	TObjectPtr<class ATPSSkillEquipmentBase> Equipment;
};
