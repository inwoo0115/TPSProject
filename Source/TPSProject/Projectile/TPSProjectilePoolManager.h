// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSProjectileType.h"
#include "TPSProjectilePoolManager.generated.h"

class ATPSProjectileBase;

UCLASS()
class TPSPROJECT_API ATPSProjectilePoolManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPSProjectilePoolManager();

	void ReturnProjectile(ATPSProjectileBase* Projectile);

	ATPSProjectileBase* GetProjectile(EProjectileType Type);

	ATPSProjectileBase* GetProjectileByID(EProjectileType Type, int32 ID);

	void InitializePool(TMap<EProjectileType, TSubclassOf<class ATPSProjectileBase>> CurrentProjectileList);

	void AddPool(EProjectileType Type, TSubclassOf<ATPSProjectileBase> ProjectileClass);

	UFUNCTION(NetMulticast, Reliable)
	void MultiCastRPCAddPool(EProjectileType Type, TSubclassOf<ATPSProjectileBase> ProjectileClass);

protected:
	TMap<EProjectileType, TArray<ATPSProjectileBase*>> Pool;

	// 발사체 클래스 목록
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EProjectileType, TSubclassOf<class ATPSProjectileBase>> ProjectileList;

	UPROPERTY()
	int32 PoolSize = 80;

};
