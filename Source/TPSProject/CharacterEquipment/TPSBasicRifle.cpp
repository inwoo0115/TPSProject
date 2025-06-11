// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSBasicRifle.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityData.h"
#include "Projectile/TPSProjectileListData.h"
#include "Character/TPSCharacterBase.h"
#include "CharacterComponent/TPSWeaponComponent.h"

ATPSBasicRifle::ATPSBasicRifle()
{
	// ��밡���� �����Ƽ ���
	static ConstructorHelpers::FObjectFinder<UTPSEquipmentAbilityData> AbilityDataRef(TEXT("/Game/TPSProject/EquipmentAbility/BasicRifleAbility.BasicRifleAbility"));
	if (AbilityDataRef.Object)
	{
		AbilityData = AbilityDataRef.Object;
	}

	// ��밡���� �߻�ü ���
	static ConstructorHelpers::FObjectFinder<UTPSProjectileListData> ListDataRef(TEXT("/Game/TPSProject/ProjectileList/BasicRifleProjectiles.BasicRifleProjectiles"));
	if (ListDataRef.Object)
	{
		ProjectileData = ListDataRef.Object;
	}

	// ���� ������ ����Ʈ ���۷���
	EquipmentIcon = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(TEXT("/Game/TPSProject/Widget/Texture/T_BasicRifleIcon.T_BasicRifleIcon")));


	// ���� �⺻��
	Damage = 10.0f;

	AttackRatio = 0.3f;

	ReloadTime = 1.5f;

	MaxAmmo = 30;

	CurrentAmmo = 30;

	RequireAmmo = 1;

	UltiGaugeRatio = 0.1f;

	EquipmentName = FText::FromString(TEXT("Basic Rifle"));

	CurrentBullet = EProjectileType::RifleBullet;
}

void ATPSBasicRifle::Fire()
{
	if (bIsReloading || CurrentAmmo < RequireAmmo)
	{
		return;
	}

	CurrentAmmo -= RequireAmmo;

	auto Character = Cast<ATPSCharacterBase>(OwnerComponent->GetOwner());
	if (Character)
	{
		// ī�޶� ���� ����Ʈ���̽�
		FVector CameraLocation = Character->GetCameraLocation();
		FRotator CameraRotation = Character->GetCameraRotation();

		FVector TraceStart = CameraLocation + CameraRotation.Vector() * 100.0f;
		FVector TraceEnd = TraceStart + CameraRotation.Vector() * 10000.0f;

		FHitResult HitResult;
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.AddIgnoredActor(GetOwner());

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams);
		FVector TargetPoint = bHit ? HitResult.ImpactPoint : TraceEnd;

		// �ѱ� ��ġ���� Ÿ�� ���� ���
		FVector MuzzleLocation = GetActorLocation() + GetActorForwardVector() * 50.0f;
		FVector ShotDirection = (TargetPoint - MuzzleLocation).GetSafeNormal();
		FRotator ShotRotation = ShotDirection.Rotation();

		// �Ѿ� ����
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// ù ��° �Ѿ� Ŭ������ ����
		auto Projectile = GetWorld()->SpawnActor<ATPSProjectileBase>(
			ProjectileData->ProjectileList[CurrentBullet],
			MuzzleLocation,
			ShotRotation,
			SpawnParams
		);

		// �Ѿ� ����ü�� ��������� ������ ����
		if (Projectile)
		{
			auto WeaponComponent = Cast<UTPSWeaponComponent>(GetOwnerComponent());
			if (WeaponComponent)
			{
				Projectile->SetDamage(WeaponComponent->EventSystem->BroadCastOnDamageCalculation(FName(TEXT("Weapon"))));
			}
		}
	}
}

void ATPSBasicRifle::Launch()
{
	bCanFire = false;

	// Attack Delay
	GetWorld()->GetTimerManager().SetTimer(FireCooldownHandle, FTimerDelegate::CreateLambda([this]()
		{
			if (CurrentAmmo > 0)
			{
				bCanFire = true;
			}
		}), AttackRatio, false);
}

void ATPSBasicRifle::Reload()
{
	if (bIsReloading || CurrentAmmo == MaxAmmo)
	{
		return;
	}

	bIsReloading = true;
	bCanFire = false;


	FTimerHandle ReloadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, FTimerDelegate::CreateLambda([this]()
		{
			CurrentAmmo = MaxAmmo;
			bIsReloading = false;
			bCanFire = true;
		}), ReloadTime, false);
}

void ATPSBasicRifle::Effect()
{
	// Ŭ���̾�Ʈ������ ����Ʈ ����
}
