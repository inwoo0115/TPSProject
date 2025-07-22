// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolManager/TPSPoolManager.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Character/TPSCharacterBase.h"
#include "CharacterComponent/TPSWeaponComponent.h"
#include "CharacterComponent/TPSSpAttackSkillComponent.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "CharacterEquipment/TPSSpAttackSkillBase.h"
#include "Projectile/TPSProjectileBase.h"

TWeakObjectPtr<ATPSPoolManager> ATPSPoolManager::Instance = nullptr;

// Sets default values
ATPSPoolManager::ATPSPoolManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 루트 컴포넌트 생성 
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	bReplicates = true;
}

// Called when the game starts or when spawned
void ATPSPoolManager::BeginPlay()
{
	Super::BeginPlay();

	//instance caching
	Instance = this;
}

void ATPSPoolManager::InitializePool(UWorld* World, TMap<EProjectileType, TSubclassOf<class ATPSProjectileBase>> ProjectileList)
{
	if (!World) return;

	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	if (!PC || !PC->GetPawn()) return;

	ATPSCharacterBase* Character = Cast<ATPSCharacterBase>(PC->GetPawn());
	if (!Character) return;


	for (const TPair<EProjectileType, TSubclassOf<ATPSProjectileBase>>& Pair : ProjectileList)
	{
		if (!Pair.Value) continue;

		TArray<ATPSProjectileBase*> PoolArray = ProjectilePool.FindOrAdd(Pair.Key);

		for (int32 i = 0; i < PoolSize; ++i)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			ATPSProjectileBase* Projectile = GetWorld()->SpawnActor<ATPSProjectileBase>(Pair.Value, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
			if (Projectile)
			{
				Projectile->SetActorHiddenInGame(true);
				Projectile->SetActorEnableCollision(false);
				Projectile->SetReplicates(false);
				Projectile->ProjectileType = Pair.Key;
				PoolArray.Add(Projectile);
			}
		}
	}
}


ATPSPoolManager* ATPSPoolManager::GetInstance(UWorld* World)
{
	if (Instance.IsValid())
	{
		return Instance.Get();
	}

	// 초기화가 안되었을 경우 월드에서 탐색
	for (TActorIterator<ATPSPoolManager> It(World); It; ++It)
	{
		Instance = *It;
		return Instance.Get();
	}

	return nullptr;
}

ATPSProjectileBase* ATPSPoolManager::GetProjectile(EProjectileType ProjectileType)
{
	TArray<ATPSProjectileBase*>* PoolPtr = ProjectilePool.Find(ProjectileType);

	if (PoolPtr && PoolPtr->Num() > 0)
	{
		ATPSProjectileBase* Projectile = PoolPtr->Pop();
		if (Projectile)
		{
			Projectile->SetActorHiddenInGame(false);
			Projectile->SetActorEnableCollision(true);
			Projectile->SetReplicates(false);
			return Projectile;
		}
	}

	return nullptr;
}

void ATPSPoolManager::ReturnProjectile(ATPSProjectileBase* Projectile)
{
	if (!Projectile) return;

	// 풀에 반환하기 전에 상태 초기화
	Projectile->SetActorHiddenInGame(true);
	Projectile->SetActorEnableCollision(false);
	Projectile->SetReplicates(false);

	// 풀에 반환
	ProjectilePool.FindOrAdd(Projectile->ProjectileType).Add(Projectile);
}
