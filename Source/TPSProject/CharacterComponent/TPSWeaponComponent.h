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
	// 공격 키 해제 어빌리티 이벤트
	FWeaponAbilityEvent OnStopFire;

	// 총알 충돌 시 어빌리티 이벤트
	FWeaponAbilityEvent OnBulletHit;

	// 장비 장착
	void EquipWeapon(TSubclassOf<ATPSWeaponBase> WeaponClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3);

	// 이벤트 시스템 등록
	void Initialize(UTPSGameplayEventSystem* InputEventSystem);


	// 무기 트리거(발사)
	void FireWeapon();

	// 무기 입력 시작
	void LaunchWeapon();

	// 무기 트리거 중지
	void ReleaseWeapon();

	// 재장전
	void ReloadWeapon();

	// 이펙트
	void EffectWeapon();

	// 무기 사용 가능
	bool GetCanLaunchWeapon();

	UPROPERTY()
	TObjectPtr<class UTPSGameplayEventSystem> EventSystem;

	UPROPERTY()
	TObjectPtr<class ATPSWeaponBase> EquippedWeapon;
};
