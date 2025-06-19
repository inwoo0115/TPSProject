// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Projectile/TPSProjectileBase.h"
#include "Projectile/TPSProjectileType.h"
#include "TPSPoolManagerConfigData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FProjectilePoolConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ATPSProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 PoolSize = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EProjectileType	Type = EProjectileType::RifleBullet;
};

UCLASS()
class TPSPROJECT_API UTPSPoolManagerConfigData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FProjectilePoolConfig> PoolConfigurations;
};
