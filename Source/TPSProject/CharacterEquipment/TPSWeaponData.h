// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Projectile/TPSProjectileBase.h"
#include "Projectile/TPSProjectileType.h"
#include "CharacterEquipmentAbility/TPSAbilityType.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSWeaponData.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSWeaponData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = ProjectileList)
	TMap<EProjectileType, TSubclassOf<ATPSProjectileBase>> ProjectileList;

	UPROPERTY(EditAnywhere, Category = EquipmentAbility)
	TMap<EAbilityType, TSubclassOf<UTPSEquipmentAbilityBase>> AbilityList;

	UPROPERTY(EditAnywhere, Category = WeaponInfo)
	float Damage;

	UPROPERTY(EditAnywhere, Category = WeaponInfo)
	float AttackRatio;

	UPROPERTY(EditAnywhere, Category = WeaponInfo)
	float ReloadTime;

	UPROPERTY(EditAnywhere, Category = WeaponInfo)
	float UltiGaugeRatio;

	UPROPERTY(EditAnywhere, Category = WeaponInfo)
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, Category = WeaponInfo)
	int32 RequireAmmo;

	UPROPERTY(EditAnywhere, Category = WeaponInfo)
	TSoftObjectPtr<UTexture2D> WeaponIcon;

	UPROPERTY(EditAnywhere, Category = WeaponInfo)
	FText WeaponName;

	UPROPERTY(EditAnywhere, Category = WeaponInfo)
	EProjectileType CurrentBullet;

	UPROPERTY(EditAnywhere, Category = WeaponInfo)
	TObjectPtr<class UNiagaraSystem> MuzzleEffect;
};