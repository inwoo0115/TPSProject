// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityData.h"

#include "TPSWeaponBase.generated.h"


UCLASS()
class TPSPROJECT_API ATPSWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:
	ATPSWeaponBase();

	// ���� ��� ���� �Լ� 
	virtual void Launch();

	virtual void Fire();

	virtual void Release();

	virtual void Reload();

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

	// ���� �߻�ü Ŭ����
	UPROPERTY()
	TObjectPtr<class UTPSProjectileListData> ProjectileData;

	// ���� �⺻��
	float Damage;

	float AttackRatio;

	float ReloadTime;

	float UltiGaugeRatio;

	int32 MaxAmmo;

	int32 CurrentAmmo;

	bool bCanFire = true;

	bool bIsReloading = false;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	UActorComponent* GetOwnerComponent() const;

protected:

	// ���� ������Ʈ
	UPROPERTY()
	TObjectPtr<class UActorComponent> OwnerComponent;
};
