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
	void EquipWeapon(TSubclassOf<ATPSWeaponBase> WeaponClass);

	// �̺�Ʈ �ý��� ���
	void Initialize(UTPSGameplayEventSystem* InputEventSystem);

	// ���� Ʈ����(�߻�)
	void FireWeapon();

	// ���� Ʈ���� ����
	void ReleaseWeapon();

	// ������
	void ReloadWeapon();

	// ����Ʈ
	void EffectWeapon();

	UPROPERTY()
	TObjectPtr<class UTPSGameplayEventSystem> EventSystem;

	UPROPERTY()
	TObjectPtr<class ATPSWeaponBase> EquippedWeapon;
};
