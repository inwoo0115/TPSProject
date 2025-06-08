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

	MaxAmmo = 30;

	CurrentAmmo = 30;

	UltiGaugeRatio = 0.1f;
}

void ATPSBasicRifle::Fire()
{
	if (!bCanFire || bIsReloading)
	{
		return;
	}

	CurrentAmmo--;
	bCanFire = false;

	auto Character = Cast<ACharacter>(OwnerComponent->GetOwner());
	if (Character)
	{
		// 카메라 기준 라인트레이스
		FVector CameraLocation;
		FRotator CameraRotation;
		Character->GetController()->GetPlayerViewPoint(CameraLocation, CameraRotation);

		FVector TraceStart = CameraLocation + CameraRotation.Vector() * 100.0f;
		FVector TraceEnd = TraceStart + CameraRotation.Vector() * 10000.0f;

		FHitResult HitResult;
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.AddIgnoredActor(GetOwner());

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams);
		FVector TargetPoint = bHit ? HitResult.ImpactPoint : TraceEnd;

		// 총구 위치에서 타겟 방향 계산
		FVector MuzzleLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
		FVector ShotDirection = (TargetPoint - MuzzleLocation).GetSafeNormal();
		FRotator ShotRotation = ShotDirection.Rotation();

		// 총알 스폰
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// 첫 번째 총알 클래스로 생성
		GetWorld()->SpawnActor<ATPSProjectileBase>(
			ProjectileData->ProjectileList[EProjectileType::RifleBullet],
			MuzzleLocation,
			ShotRotation,
			SpawnParams
		);
	}

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
