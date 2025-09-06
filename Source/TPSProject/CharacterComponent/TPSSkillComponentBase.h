// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSSkillComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UTPSSkillComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UTPSSkillComponentBase();

	// ��� ����
	virtual void Equip(TSubclassOf<ATPSAbilityEquipmentBase> EquipmentClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3);

	// ��ų ��� 
	virtual void CastSkill();

	// ��ų �Է� ó��
	virtual void LaunchSkill();

	// ��ų ��� ���� 
	virtual bool GetCanCastSkill();

	const ATPSAbilityEquipmentBase* GetEquipment() const { return Equipment; }

	UPROPERTY(Replicated)
	TObjectPtr<class ATPSAbilityEquipmentBase> Equipment;

	virtual void InitEquipmentAbilityList();

protected:
	// RPC
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)
	void ServerRPCEquip(TSubclassOf<ATPSAbilityEquipmentBase> EquipmentClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3);
};
