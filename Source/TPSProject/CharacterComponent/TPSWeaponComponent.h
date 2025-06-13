// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "TPSWeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponAbilityEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UTPSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTPSWeaponComponent();

	// ���� Ű ���� �����Ƽ �̺�Ʈ
	FWeaponAbilityEvent OnStopFire;

	// �Ѿ� �浹 �� �����Ƽ �̺�Ʈ
	FWeaponAbilityEvent OnBulletHit;

	// ��� ����
	void EquipWeapon(TSubclassOf<ATPSWeaponBase> WeaponClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3);

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

	// ���� ����
	bool GetCanReloadWeapon();

	const ATPSWeaponBase* GetWeapon() const { return EquippedWeapon; }

	UPROPERTY(Replicated)
	TObjectPtr<class ATPSWeaponBase> EquippedWeapon;

protected:
	// RPC
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)
	void ServerRPCEquipWeapon(TSubclassOf<ATPSWeaponBase> WeaponClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3);

};
