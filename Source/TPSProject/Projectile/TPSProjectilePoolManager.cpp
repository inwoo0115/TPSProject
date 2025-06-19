// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TPSProjectilePoolManager.h"
#include "TPSProjectileBase.h"

// Sets default values
ATPSProjectilePoolManager::ATPSProjectilePoolManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��Ʈ ������Ʈ ���� 
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void ATPSProjectilePoolManager::ReturnProjectile(ATPSProjectileBase* Projectile)
{
	Projectile->ResetProjectile();
}

ATPSProjectileBase* ATPSProjectilePoolManager::GetProjectile(EProjectileType Type)
{
	if (Pool.Contains(Type))
	{
		for (ATPSProjectileBase* P : Pool[Type])
		{
			if (P->IsHidden()) // �Ǵ� CustomFlag ���
			{
				return P;
			}
		}
	}
	return nullptr;
}

ATPSProjectileBase* ATPSProjectilePoolManager::GetProjectileByID(EProjectileType Type, int32 ID)
{
	if (Pool.Contains(Type))
	{
		for (ATPSProjectileBase* P : Pool[Type])
		{
			if (P->IsHidden() && P->ProjectileID == ID)
			{
				return P;
			}
		}
	}
	return nullptr;
}

void ATPSProjectilePoolManager::InitializePool(TMap<EProjectileType, TSubclassOf<class ATPSProjectileBase>> CurrentProjectileList)
{
	ProjectileList = CurrentProjectileList; // ���޹��� Projectile Ŭ���� ���� ����

	for (const TPair<EProjectileType, TSubclassOf<ATPSProjectileBase>>& Entry : ProjectileList)
	{
		EProjectileType Type = Entry.Key;
		TSubclassOf<ATPSProjectileBase> ClassToSpawn = Entry.Value;

		if (!ClassToSpawn) continue;

		AddPool(Type, ClassToSpawn);
		MultiCastRPCAddPool(Type, ClassToSpawn);
	}
}

void ATPSProjectilePoolManager::AddPool(EProjectileType Type, TSubclassOf<ATPSProjectileBase> ProjectileClass)
{
	// ������Ʈ ����
	FActorSpawnParameters SpawnParams;

	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetInstigator();
	// �浹 ���� ����
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	TArray<ATPSProjectileBase*>& TypePool = Pool.FindOrAdd(Type);

	for (int32 i = 0; i < PoolSize; ++i)
	{

		ATPSProjectileBase* Projectile = GetWorld()->SpawnActor<ATPSProjectileBase>(
			ProjectileClass,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			SpawnParams
		);

		if (Projectile)
		{
			Projectile->SetActorEnableCollision(false);
			Projectile->SetActorHiddenInGame(true);
			Projectile->SetReplicates(true);
			Projectile->SetReplicateMovement(true);
			Projectile->ProjectileID = i;

			TypePool.Add(Projectile);
		}
	}
}

void ATPSProjectilePoolManager::MultiCastRPCAddPool_Implementation(EProjectileType Type, TSubclassOf<ATPSProjectileBase> ProjectileClass)
{
	AddPool(Type, ProjectileClass);
}
