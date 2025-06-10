// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityData.h"
#include "TPSSkillEquipmentBase.generated.h"

UCLASS()
class TPSPROJECT_API ATPSSkillEquipmentBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPSSkillEquipmentBase();

	// ��� ��� ���� �Լ�
	virtual void Cast();
	
	virtual void Effect();

	// Ư�� �迭 �ʱ�ȭ
	virtual void ClearAbilitySlot();

	// ������Ʈ�� Ư�� ����
	virtual void InitializeAbilities();

	// ���� ���� �� ���� ������Ʈ ���
	virtual void InitializeComponent(UActorComponent* NewComponent);

	// ������ ���¿��� Ư�� �ʱ�ȭ
	virtual void InitializeAbilitiesFromDataAsset(EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3);

	// Ư�� ������ ����
	UPROPERTY()
	TObjectPtr<class UTPSEquipmentAbilityData> AbilityData;

	// ��밡���� ��ü Ư�� �迭
	UPROPERTY()
	TArray<class UTPSEquipmentAbilityBase*> AbilitySlot;

	// ��� ��ų �⺻��
	float Damage;
	
	float CoolTime;
	
	float UltiGaugeRatio;

	bool bCanCast = true;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	UActorComponent* GetOwnerComponent() const;

protected:

	// ���� ������Ʈ
	UPROPERTY()
	TObjectPtr<class UActorComponent> OwnerComponent;
};
