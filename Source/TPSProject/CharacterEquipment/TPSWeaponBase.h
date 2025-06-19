// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile/TPSProjectileType.h"
#include "TPSAbilityEquipmentBase.h"
#include "TPSWeaponBase.generated.h"

USTRUCT(BlueprintType)
struct FWeaponContext
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRatio = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UltiGaugeRatio = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmmo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmmo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequireAmmo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> WeaponIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProjectileType CurrentBullet = EProjectileType::RifleBullet;
};


UCLASS()
class TPSPROJECT_API ATPSWeaponBase : public ATPSAbilityEquipmentBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	// 무기 기능 구현 함수 
	virtual void Launch();

	virtual void Fire();

	virtual void Reload();

	virtual void Effect();

	// Getter
	bool CanReload();

	bool CanFire();

	// 무기 정보 초기화
	void SetWeaponContextFromData();

	// 컴포넌트에 장비 특성 적용
	virtual void InitializeAbilities() override;

	// 무기 정보 데이터 에셋
	UPROPERTY(Replicated)
	TObjectPtr<class UTPSWeaponData> WeaponData;

	UPROPERTY(Replicated)
	bool bCanFire = true;

	UPROPERTY(Replicated)
	bool bIsReloading = false;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FWeaponContext GetWeaponContext() const;

	// 발사체 클래스 목록
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EProjectileType, TSubclassOf<class ATPSProjectileBase>> ProjectileList;

	UPROPERTY(ReplicatedUsing=OnRepInitializePool)
	TObjectPtr<class ATPSProjectilePoolManager> Pool;

	UFUNCTION()
	void OnRepInitializePool();

	UFUNCTION()
	void InitializePool();

	// Predict Projectile Getter Setter
	int32 GetPredictProjectileIndex(); 

	void SetPredictProjectileIndex(int32 Index);

protected:
	UPROPERTY()
	int32 PredictProjectileIndex = 0;

	// 사격 딜레이 타이머
	FTimerHandle FireCooldownHandle;

	// RPC
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// 무기 정보 구조체
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FWeaponContext WeaponContext;

};
