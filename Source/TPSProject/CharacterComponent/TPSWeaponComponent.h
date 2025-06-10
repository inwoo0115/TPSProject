// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "TPSGameplayEventSystem.h"
#include "TPSWeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponAbilityEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UTPSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// ���� Ű ���� �����Ƽ �̺�Ʈ
	FWeaponAbilityEvent OnStopFire;

	// �Ѿ� �浹 �� �����Ƽ �̺�Ʈ
	FWeaponAbilityEvent OnBulletHit;

	// ��� ����
	void EquipWeapon(TSubclassOf<ATPSWeaponBase> WeaponClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3);

	// �̺�Ʈ �ý��� ���
	void Initialize(UTPSGameplayEventSystem* InputEventSystem);


	// ���� Ʈ����(�߻�)
	void FireWeapon();

	// ���� �Է� ����
	void LaunchWeapon();

	// ���� Ʈ���� ����
	void ReleaseWeapon();

	// ������
	void ReloadWeapon();

	// ����Ʈ
	void EffectWeapon();

	// ���� ��� ����
	bool GetCanLaunchWeapon();

	UPROPERTY()
	TObjectPtr<class UTPSGameplayEventSystem> EventSystem;

	UPROPERTY()
	TObjectPtr<class ATPSWeaponBase> EquippedWeapon;
};
