// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile/TPSProjectileType.h"
#include "TPSPoolManager.generated.h"

class ATPSProjectileBase;

UCLASS()
class TPSPROJECT_API ATPSPoolManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPSPoolManager();

	static ATPSPoolManager* GetInstance(UWorld* World);

	ATPSProjectileBase* GetProjectile(EProjectileType ProjectileType);

	void ReturnProjectile(ATPSProjectileBase* Projectile);

	void InitializePool(UWorld* World);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	static TWeakObjectPtr<ATPSPoolManager> Instance;

	TMap<EProjectileType, TArray<ATPSProjectileBase*>> ProjectilePool;

	int32 PoolSize = 100;
};
