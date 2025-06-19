// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/TPSPoolManagerSubsystem.h"
#include "TPSPoolManagerSubsystem.h"
#include "TPSPoolManagerConfigData.h"
#include "Projectile/TPSProjectilePoolManager.h"

void UTPSPoolManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	
	PoolDataAsset = LoadObject<UTPSPoolManagerConfigData>(nullptr, TEXT("/Game/TPSProject/GameData/PoolManagerData.PoolManagerData"));
	
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UTPSPoolManagerSubsystem::OnPostLoadMap);

	// 에디터에서 바로 맵 진입했을 때 초기화 처리
	if (UWorld* World = GetWorld())
	{
		FString MapName = World->GetMapName();
		if (MapName.Contains("DemoMultiLevel"))
		{
			if (PoolDataAsset)
			{
				InitializePool(PoolDataAsset->PoolConfigurations);
			}
		}
	}
}

void UTPSPoolManagerSubsystem::Deinitialize()
{
	FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);
	ProjectilePools.Empty();
	Super::Deinitialize();
}

void UTPSPoolManagerSubsystem::InitializePool(const TArray<FProjectilePoolConfig>& PoolConfigs)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("InitializePool fail"));
		return;
	}

	// 기존 풀 클리어
	ProjectilePools.Empty();

	for (const FProjectilePoolConfig& Config : PoolConfigs)
	{
		if (!Config.ProjectileClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("InitializePool fail by None Class"));
			continue;
		}

		TArray<ATPSProjectileBase*>& Pool = ProjectilePools.FindOrAdd(Config.Type);

		for (int32 i = 0; i < Config.PoolSize; ++i)
		{
			// 투사체 생성
			ATPSProjectileBase* NewProj = World->SpawnActor<ATPSProjectileBase>(Config.ProjectileClass, FVector::ZeroVector, FRotator::ZeroRotator);
			if (NewProj)
			{
				NewProj->ProjectileID = i;
				NewProj->ResetProjectile();
				Pool.Add(NewProj);
			}
		}
	}
}

ATPSProjectileBase* UTPSPoolManagerSubsystem::GetProjectile(EProjectileType Type)
{
	if (ProjectilePools.Contains(Type))
	{
		for (ATPSProjectileBase* P : ProjectilePools[Type])
		{
			if (P->IsHidden())
			{
				return P;
			}
		}
	}
	return nullptr;
}

ATPSProjectileBase* UTPSPoolManagerSubsystem::GetProjectileByID(EProjectileType Type, int32 ID)
{
	if (ProjectilePools.Contains(Type))
	{
		for (ATPSProjectileBase* P : ProjectilePools[Type])
		{
			if (P->IsHidden() && P->ProjectileID == ID)
			{
				return P;
			}
		}
	}
	return nullptr;
}

void UTPSPoolManagerSubsystem::ReturnProjectile(ATPSProjectileBase* Projectile)
{
	Projectile->ResetProjectile();
}

void UTPSPoolManagerSubsystem::OnPostLoadMap(UWorld* LoadedWorld)
{
	if (!LoadedWorld)
		return;

	FString MapName = LoadedWorld->GetMapName();

	// 원하는 레벨 이름으로 체크 가능
	if (LoadedWorld->GetMapName().Contains("DemoMultiLevel"))
	{
		if (PoolDataAsset)
		{
			InitializePool(PoolDataAsset->PoolConfigurations);
		}
	}
}
