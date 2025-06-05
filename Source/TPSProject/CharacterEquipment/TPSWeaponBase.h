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

	UPROPERTY()
	TObjectPtr<class UTPSEquipmentAbilityData> AbilityData;

	UPROPERTY()
	TArray<class UTPSEquipmentAbilityBase*> AbilitySlot;

protected:
	UPROPERTY()
	TObjectPtr<class UActorComponent> OwnerComponent;
};
