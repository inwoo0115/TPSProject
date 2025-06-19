// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSWeaponBase.h"
#include "Character/TPSCharacterBase.h"	
#include "Projectile/TPSProjectileBase.h"
#include "Projectile/TPSProjectilePoolManager.h"
#include "TPSWeaponData.h"
#include "Net/UnrealNetwork.h"
#include "GameInstance/TPSGameplayEventSubsystem.h"
#include "GameInstance/TPSPoolManagerSubsystem.h"

void ATPSWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	// ������ �� UI ���� ������Ʈ
	if (EventSystem)
	{
		EventSystem->OnAmmoChange.Broadcast(WeaponContext.CurrentAmmo, WeaponContext.MaxAmmo);
	}
}

void ATPSWeaponBase::InitializeAbilities()
{
	for (UTPSEquipmentAbilityBase* Ability : AbilitySlot)
	{
		if (Ability)
		{
			Ability->InitializeWeaponAbility(WeaponContext);
		}
	}
}


void ATPSWeaponBase::Launch()
{
	bCanFire = false;

	// Attack Delay
	GetWorld()->GetTimerManager().SetTimer(FireCooldownHandle, FTimerDelegate::CreateLambda([this]()
		{
			if (WeaponContext.CurrentAmmo > 0)
			{
				bCanFire = true;
			}
		}), WeaponContext.AttackRatio, false);
}

void ATPSWeaponBase::Fire()
{
	if (bIsReloading || WeaponContext.CurrentAmmo < WeaponContext.RequireAmmo)
	{
		return;
	}

	auto Character = Cast<ATPSCharacterBase>(OwnerComponent->GetOwner());

	if (!HasAuthority() || !Character->IsLocallyControlled())
	{
		return;
	}

	WeaponContext.CurrentAmmo -= WeaponContext.RequireAmmo;

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

		if (HasAuthority())
		{
			GetGameInstance()->GetSubsystem<UTPSPoolManagerSubsystem>()->GetProjectile(WeaponContext.CurrentBullet)->MulticastRPCActivate(MuzzleLocation, ShotDirection, ShotRotation);
		}
		

		/*if (HasAuthority())
			Pool->GetProjectile(WeaponContext.CurrentBullet)->MulticastRPCActivate(MuzzleLocation, ShotDirection, ShotRotation);
		else
		{
			Pool->GetProjectileByID(WeaponContext.CurrentBullet, PredictProjectileIndex)->FireInLocal(MuzzleLocation, ShotDirection, ShotRotation);
		}*/
		// �Ѿ� ����
		/*FActorSpawnParameters SpawnParams;

		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = GetInstigator();*/

		// ���� ���� ����
		//SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//SpawnParams.bDeferConstruction = true;

		// ù ��° �Ѿ� Ŭ������ ����
	/*	auto Projectile = GetWorld()->SpawnActor<ATPSProjectileBase>(
			ProjectileList[WeaponContext.CurrentBullet],
			MuzzleLocation,
			ShotRotation,
			SpawnParams
		);*/

		// ���� �� ��� ���ø����̼� or Ŭ���̾�Ʈ �� ��� ���� �߻�ü �迭�� �߰�
		//if (Projectile)
		//{
		//	// �߻�ü ID �ο�
		//	Projectile->ProjectileID = GetNextProjectileID();

		//	if (HasAuthority())
		//	{
		//		LastProjectileID = Projectile->ProjectileID;
		//	}
		//	else
		//	{
		//		PredictedProjectiles.Add(Projectile->ProjectileID, Projectile);
		//	}
		//	UE_LOG(LogTemp, Warning, TEXT("%d"), Projectile->ProjectileID);
		//	FTransform SpawnTransfrom = FTransform(ShotRotation, MuzzleLocation);
		//	Projectile->FinishSpawning(SpawnTransfrom);
		//}

		// ���� �߻�Ǹ� UI ������Ʈ
		if (EventSystem && Character->IsLocallyControlled())
		{
			EventSystem->OnAmmoChange.Broadcast(WeaponContext.CurrentAmmo, WeaponContext.MaxAmmo);
		}
	}
}

void ATPSWeaponBase::Reload()
{
	if (bIsReloading || WeaponContext.CurrentAmmo == WeaponContext.MaxAmmo)
	{
		return;
	}
	bCanFire = false;
	bIsReloading = true;

	FTimerHandle ReloadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, FTimerDelegate::CreateLambda([this]()
		{
			WeaponContext.CurrentAmmo = WeaponContext.MaxAmmo;
			bIsReloading = false;
			bCanFire = true;

			// ������ �� UI ������Ʈ
			if (EventSystem)
			{
				EventSystem->OnAmmoChange.Broadcast(WeaponContext.CurrentAmmo, WeaponContext.MaxAmmo);
			}
		}), WeaponContext.ReloadTime, false);
}

void ATPSWeaponBase::Effect()
{
	// TODO: Ŭ���̾�Ʈ���� ����Ʈ ����

}

bool ATPSWeaponBase::CanReload()
{
	return !bIsReloading && !(WeaponContext.CurrentAmmo == WeaponContext.MaxAmmo);
}

bool ATPSWeaponBase::CanFire()
{
	return bCanFire;
}

void ATPSWeaponBase::SetWeaponContextFromData()
{
	if (WeaponData)
	{
		ProjectileList = WeaponData->ProjectileList;

		AbilityList = WeaponData->AbilityList;

		WeaponContext.Damage = WeaponData->Damage;

		WeaponContext.AttackRatio = WeaponData->AttackRatio;
		
		WeaponContext.ReloadTime = WeaponData->ReloadTime;
		
		WeaponContext.UltiGaugeRatio = WeaponData->UltiGaugeRatio;
		
		WeaponContext.MaxAmmo = WeaponData->MaxAmmo;
		
		WeaponContext.CurrentAmmo = WeaponData->MaxAmmo;

		WeaponContext.RequireAmmo = WeaponData->RequireAmmo;

		WeaponContext.WeaponIcon = WeaponData->WeaponIcon;

		WeaponContext.WeaponName = WeaponData->WeaponName;

		WeaponContext.CurrentBullet = WeaponData->CurrentBullet;
	}
}

FWeaponContext ATPSWeaponBase::GetWeaponContext() const
{
	return WeaponContext;
}

void ATPSWeaponBase::OnRepInitializePool()
{
	InitializePool();
}

void ATPSWeaponBase::InitializePool()
{
	// ������Ʈ ����
	FActorSpawnParameters SpawnParams;

	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetInstigator();
	// �浹 ���� ����
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	Pool = GetWorld()->SpawnActor<ATPSProjectilePoolManager>(
		ATPSProjectilePoolManager::StaticClass(),
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		SpawnParams
	);
	Pool->InitializePool(ProjectileList);
}

int32 ATPSWeaponBase::GetPredictProjectileIndex()
{
	// ��밡���� ����ü ��������
	auto PredictProjectile = Pool->GetProjectile(WeaponContext.CurrentBullet);
	if (PredictProjectile)
	{
		PredictProjectileIndex = PredictProjectile->ProjectileID;
		return PredictProjectileIndex;
	}
	return 0;
}

void ATPSWeaponBase::SetPredictProjectileIndex(int32 Index)
{
	PredictProjectileIndex = Index;
}

void ATPSWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPSWeaponBase, WeaponData);
	DOREPLIFETIME(ATPSWeaponBase, bCanFire);
	DOREPLIFETIME(ATPSWeaponBase, bIsReloading);
	DOREPLIFETIME(ATPSWeaponBase, WeaponContext);
	DOREPLIFETIME(ATPSWeaponBase, Pool);
}
