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
	// 장비 장착
	virtual void Equip(TSubclassOf<ATPSSkillEquipmentBase> EquipmentClass);

	// 스킬 시전
	virtual void CastSkill();

	// 스킬 이펙트
	virtual void EffectSkill();

	// 이벤트 시스템 등록
	void Initialize(UTPSGameplayEventSystem* InputEventSystem);

	UPROPERTY()
	TObjectPtr<class UTPSGameplayEventSystem> EventSystem;

	UPROPERTY()
	TObjectPtr<class ATPSSkillEquipmentBase> Equipment;
};
