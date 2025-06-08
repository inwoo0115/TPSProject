// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "TPSBasicRifle.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSBasicRifle : public ATPSWeaponBase
{
	GENERATED_BODY()

public:
	ATPSBasicRifle();

	void Fire() override;

	void Reload() override;

protected:
	// 무기 기본값
	float Damage = 10.0f;
	
	float AttackRatio = 0.3f;
	
	int32 MaxAmmo = 30;

	int32 CurrentAmmo = 30;

	// 무기 추가 설정
	bool HasLazerMode = false;
};
