// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSWeaponBase.generated.h"


UCLASS()
class TPSPROJECT_API ATPSWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	

	// Ư�� �迭�� �߰�
	virtual void AddAbility(UTPSEquipmentAbilityBase* NewAbility);

	// Ư�� �迭 �ʱ�ȭ
	virtual void ClearAbilitySlot();

	// ������Ʈ�� Ư�� ����
	virtual void InitializeAbilities();

	// ���� ���� �� ���� ������Ʈ ���
	virtual void InitializeComponent(UActorComponent* InitializeComponent);

	// Ư�� ������ ����
	UPROPERTY()
	TObjectPtr<class UTPSEquipmentAbilityData> AbilityData;

	// ��밡���� ��ü Ư�� �迭
	UPROPERTY()
	TArray<class UTPSEquipmentAbilityBase*> AbilitySlot;

protected:

	// ���� ������Ʈ
	UPROPERTY()
	TObjectPtr<class UActorComponent> OwnerComponent;

	// ���� �߻�ü Ŭ����
	UPROPERTY()
	TObjectPtr<class UTPSProjectileListData> Projectiles;

	// ���� �⺻��
	float Damage;

	float AttackRatio;

	int32 MaxAmmo;

	int32 CurrentAmmo;

};
