// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterEquipmentAbility/TPSAbilityType.h"
#include "Projectile/TPSProjectileType.h"
#include "CharacterComponent/TPSGameplayEventSystem.h"
#include "TPSWeaponBase.generated.h"

USTRUCT(BlueprintType)
struct FWeaponContext
{
	GENERATED_BODY()

	// 무기 특성 목록
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EProjectileType, TSubclassOf<class ATPSProjectileBase>> ProjectileList;

	// 무기 발사체 클래스 목록
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EAbilityType, TSubclassOf<class UTPSEquipmentAbilityBase>> AbilityList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UltiGaugeRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequireAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> WeaponIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProjectileType CurrentBullet;
};


UCLASS()
class TPSPROJECT_API ATPSWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:
	ATPSWeaponBase();

	// 무기 기능 구현 함수 
	virtual void Launch();

	virtual void Fire();

	virtual void Release();

	virtual void Reload();

	virtual void Effect();

	// Getter
	bool CanReload();

	bool CanFire();

	// 무기 정보 초기화
	void SetWeaponContextFromData();

	// 컴포넌트에 특성 적용
	void InitializeAbilities();

	// 무기 의존성 주입
	void InitializeComponentAndEventSystem(UActorComponent* InitComponent, UTPSGameplayEventSystem* InitEventSystem);

	// 데이터 에셋에서 특성 초기화
	void InitializeAbilitiesFromDataAsset(EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3);

	// 사용가능한 전체 특성 배열
	UPROPERTY()
	TArray<class UTPSEquipmentAbilityBase*> AbilitySlot;

	// 무기 정보 데이터 에셋
	UPROPERTY()
	TObjectPtr<class UTPSWeaponData> WeaponData;

	bool bCanFire = true;

	bool bIsReloading = false;

	//EProjectileType CurrentBullet;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	UActorComponent* GetOwnerComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FWeaponContext GetWeaponContext() const;

protected:
	// 사격 딜레이 타이머
	FTimerHandle FireCooldownHandle;

	// 오너 컴포넌트
	UPROPERTY()
	TObjectPtr<class UActorComponent> OwnerComponent;

	// 이벤트 시스템 오브젝트
	UPROPERTY()
	TObjectPtr<class UTPSGameplayEventSystem> EventSystem;

	// 무기 정보 구조체
	UPROPERTY()
	FWeaponContext WeaponContext;


};
