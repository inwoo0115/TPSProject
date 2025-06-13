// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSWeaponBase.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "Character/TPSCharacterBase.h"
#include "Projectile/TPSProjectileBase.h"
#include "TPSWeaponData.h"
#include "CharacterComponent/TPSWeaponComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"


ATPSWeaponBase::ATPSWeaponBase()
{
	// 루트 컴포넌트 생성 
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	bReplicates = true;
	SetReplicateMovement(true);
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

void ATPSWeaponBase::InitializeComponent(UActorComponent* InitComponent)
{
	OwnerComponent = InitComponent;
}

void ATPSWeaponBase::InitializeAbilitiesFromDataAsset(EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
	// Ability1
	if (AbilityList.Contains(Ability1))
	{
		UTPSEquipmentAbilityBase* NewAbility1 = NewObject<UTPSEquipmentAbilityBase>(this, AbilityList[Ability1]);
		if (NewAbility1)
		{
			AbilitySlot.Add(NewAbility1);
		}
	}
	// Ability2
	if (AbilityList.Contains(Ability2))
	{
		UTPSEquipmentAbilityBase* NewAbility2 = NewObject<UTPSEquipmentAbilityBase>(this, AbilityList[Ability2]);
		if (NewAbility2)
		{
			AbilitySlot.Add(NewAbility2);
		}
	}
	// Ability3
	if (AbilityList.Contains(Ability3))
	{
		UTPSEquipmentAbilityBase* NewAbility3 = NewObject<UTPSEquipmentAbilityBase>(this, AbilityList[Ability3]);
		if (NewAbility3)
		{
			AbilitySlot.Add(NewAbility3);
		}
	}
}

void ATPSWeaponBase::OnRep_AbilitySlot()
{
	for (UTPSEquipmentAbilityBase* Ability : AbilitySlot)
	{
		if (Ability)
		{
			// 델리게이트만 조정하게 변경
			// Ability->InitializeWeaponAbility(WeaponContext);
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
		SpawnParams.Owner = this;
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
			auto WeaponComponent = Cast<UTPSWeaponComponent>(GetOwnerComponent());
			if (WeaponComponent)
			{
				//Event System 기반 데미지 세팅
			}
		}
	}
}

void ATPSWeaponBase::Release()
{
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
		}), WeaponContext.ReloadTime, false);
}

void ATPSWeaponBase::Effect()
{
	// 클라이언트에서 이펙트 생성
	// 오브젝트 풀링 해야 할까...?
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

UActorComponent* ATPSWeaponBase::GetOwnerComponent() const
{
	return OwnerComponent;
}

FWeaponContext ATPSWeaponBase::GetWeaponContext() const
{
	return WeaponContext;
}

void ATPSWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPSWeaponBase, AbilitySlot);
	DOREPLIFETIME(ATPSWeaponBase, WeaponData);
	DOREPLIFETIME(ATPSWeaponBase, bCanFire);
	DOREPLIFETIME(ATPSWeaponBase, bIsReloading);
	DOREPLIFETIME(ATPSWeaponBase, OwnerComponent);
	DOREPLIFETIME(ATPSWeaponBase, WeaponContext);
}

bool ATPSWeaponBase::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (UTPSEquipmentAbilityBase* Ability : AbilitySlot)
	{
		if (Ability)
		{
			WroteSomething |= Channel->ReplicateSubobject(Ability, *Bunch, *RepFlags);
		}
	}

	return WroteSomething;
}
