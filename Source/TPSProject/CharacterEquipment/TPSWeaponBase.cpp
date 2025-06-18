// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSWeaponBase.h"
#include "Character/TPSCharacterBase.h"	
#include "Projectile/TPSProjectileBase.h"
#include "TPSWeaponData.h"
#include "Net/UnrealNetwork.h"
#include "GameInstance/TPSGameplayEventSubsystem.h"

void ATPSWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	// 시작할 때 UI 정보 업데이트
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

	WeaponContext.CurrentAmmo -= WeaponContext.RequireAmmo;

	auto Character = Cast<ATPSCharacterBase>(OwnerComponent->GetOwner());
	if (Character)
	{
		// 카메라 기준 라인트레이스
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

		// 총구 위치에서 타겟 방향 계산
		FVector MuzzleLocation = GetActorLocation() + GetActorForwardVector() * 50.0f;
		FVector ShotDirection = (TargetPoint - MuzzleLocation).GetSafeNormal();
		FRotator ShotRotation = ShotDirection.Rotation();

		// 총알 스폰
		FActorSpawnParameters SpawnParams;

		// 서버에서 오너 컨트롤러 설정해서 리플리케이션 제한
		if (HasAuthority())
		{
			SpawnParams.Owner = Character->GetController();
		}
		SpawnParams.Instigator = GetInstigator();

		// 첫 번째 총알 클래스로 생성
		auto Projectile = GetWorld()->SpawnActor<ATPSProjectileBase>(
			ProjectileList[WeaponContext.CurrentBullet],
			MuzzleLocation,
			ShotRotation,
			SpawnParams
		);

		// 총알 구조체가 만들어지면 데미지 설정
		if (Projectile)
		{
			//Event System 기반 데미지 세팅
		}

		// 총이 발사되면 UI 업데이트
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

			// 재장전 시 UI 업데이트
			if (EventSystem)
			{
				EventSystem->OnAmmoChange.Broadcast(WeaponContext.CurrentAmmo, WeaponContext.MaxAmmo);
			}
		}), WeaponContext.ReloadTime, false);
}

void ATPSWeaponBase::Effect()
{
	// TODO: 클라이언트에서 이펙트 생성

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

void ATPSWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPSWeaponBase, WeaponData);
	DOREPLIFETIME(ATPSWeaponBase, bCanFire);
	DOREPLIFETIME(ATPSWeaponBase, bIsReloading);
	DOREPLIFETIME(ATPSWeaponBase, WeaponContext);
}
