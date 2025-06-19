// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TPSPoolManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSPoolManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

	// 풀 매니저 참조 제공
	//ATPSProjectilePoolManager* GetPoolManager() const { return PoolManager; }

	// 월드 파괴 시 클린업
	virtual void Deinitialize() override;

	// 필요시 수동으로 매니저 지정
	//void SetPoolManager(ATPSProjectilePoolManager* InManager) { PoolManager = InManager; }

	UFUNCTION()
	void InitializePool(const TArray<FProjectilePoolConfig>& PoolConfigs);

	UFUNCTION()
	ATPSProjectileBase* GetProjectile(EProjectileType Type);

	UFUNCTION()
	ATPSProjectileBase* GetProjectileByID(EProjectileType Type, int32 ID);

	// 투사체 반환
	UFUNCTION()
	void ReturnProjectile(ATPSProjectileBase* Projectile);

	void OnPostLoadMap(UWorld* LoadedWorld);

private:

	// EProjectileType별로 관리되는 투사체 풀
	TMap<EProjectileType, TArray<ATPSProjectileBase*>> ProjectilePools;

	TObjectPtr<class UTPSPoolManagerConfigData> PoolDataAsset;
};
