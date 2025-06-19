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

	// Ǯ �Ŵ��� ���� ����
	//ATPSProjectilePoolManager* GetPoolManager() const { return PoolManager; }

	// ���� �ı� �� Ŭ����
	virtual void Deinitialize() override;

	// �ʿ�� �������� �Ŵ��� ����
	//void SetPoolManager(ATPSProjectilePoolManager* InManager) { PoolManager = InManager; }

	UFUNCTION()
	void InitializePool(const TArray<FProjectilePoolConfig>& PoolConfigs);

	UFUNCTION()
	ATPSProjectileBase* GetProjectile(EProjectileType Type);

	UFUNCTION()
	ATPSProjectileBase* GetProjectileByID(EProjectileType Type, int32 ID);

	// ����ü ��ȯ
	UFUNCTION()
	void ReturnProjectile(ATPSProjectileBase* Projectile);

	void OnPostLoadMap(UWorld* LoadedWorld);

private:

	// EProjectileType���� �����Ǵ� ����ü Ǯ
	TMap<EProjectileType, TArray<ATPSProjectileBase*>> ProjectilePools;

	TObjectPtr<class UTPSPoolManagerConfigData> PoolDataAsset;
};
