// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSBasicRifle.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityData.h"
#include "Projectile/TPSProjectileListData.h"
#include "GameFramework/Character.h"

ATPSBasicRifle::ATPSBasicRifle()
{
	static ConstructorHelpers::FObjectFinder<UTPSEquipmentAbilityData> AbilityDataRef(TEXT("/Game/TPSProject/EquipmentAbility/BasicRifleAbility.BasicRifleAbility"));
	if (AbilityDataRef.Object)
	{
		AbilityData = AbilityDataRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UTPSProjectileListData> ListDataRef(TEXT("/Game/TPSProject/ProjectileList/BasicRifleProjectiles.BasicRifleProjectiles"));
	if (ListDataRef.Object)
	{
		ProjectileData = ListDataRef.Object;
	}

	// 무기 기본값
	Damage = 10.0f;

	AttackRatio = 0.3f;

	ReloadTime = 1.5f;

	MaxAmmo = 10;

	CurrentAmmo = 10;
}

void ATPSBasicRifle::Fire()
{
	if (!bCanFire || bIsReloading)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("<Ability Update> Damage: %f, Max Ammo: %d"), Damage, MaxAmmo);
	if (CurrentAmmo <= 0)
	{
		Reload();
		return;
	}

	CurrentAmmo--;
	bCanFire = false;

	// 총알 발사
	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
	FRotator SpawnRotation = GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	// 첫 번째 총알 클래스로 생성
	GetWorld()->SpawnActor<ATPSProjectileBase>(ProjectileData->ProjectileList[EProjectileType::RifleBullet], SpawnLocation, SpawnRotation, SpawnParams);


	GetWorld()->GetTimerManager().SetTimer(FireCooldownHandle, FTimerDelegate::CreateLambda([this]()
		{
			bCanFire = true;
		}), AttackRatio, false);
}

void ATPSBasicRifle::Reload()
{
	if (bIsReloading || CurrentAmmo == MaxAmmo)
	{
		return;
	}

	bIsReloading = true;


	FTimerHandle ReloadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, FTimerDelegate::CreateLambda([this]()
		{
			CurrentAmmo = MaxAmmo;
			bIsReloading = false;
		}), ReloadTime, false);
}
