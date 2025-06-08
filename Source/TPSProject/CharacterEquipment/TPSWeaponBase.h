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
	// 무기 기능 구현 함수 
	virtual void Fire();

	virtual void Release();

	virtual void Reload();

	// 특성 배열 초기화
	virtual void ClearAbilitySlot();

	// 컴포넌트에 특성 적용
	virtual void InitializeAbilities();

	// 무기 장착 시 오너 컴포넌트 등록
	virtual void InitializeComponent(UActorComponent* InitializeComponent);

	// 데이터 에셋에서 특성 초기화
	virtual void InitializeAbilitiesFromDataAsset();

	// 특성 데이터 에셋
	UPROPERTY()
	TObjectPtr<class UTPSEquipmentAbilityData> AbilityData;

	// 사용가능한 전체 특성 배열
	UPROPERTY()
	TArray<class UTPSEquipmentAbilityBase*> AbilitySlot;

protected:

	// 오너 컴포넌트
	UPROPERTY()
	TObjectPtr<class UActorComponent> OwnerComponent;

	// 무기 발사체 클래스
	UPROPERTY()
	TObjectPtr<class UTPSProjectileListData> Projectiles;

	// 무기 기본값
	float Damage;

	float AttackRatio;

	int32 MaxAmmo;

	int32 CurrentAmmo;

	bool bCanFire = true;

	bool bIsReloading = false;
};
