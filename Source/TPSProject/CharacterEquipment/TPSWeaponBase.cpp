// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSWeaponBase.h"
#include "Character/TPSCharacterBase.h"	
#include "Projectile/TPSProjectileBase.h"
#include "TPSWeaponData.h"
#include "Net/UnrealNetwork.h"
#include "GameInstance/TPSGameplayEventSubsystem.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"
#include "NiagaraFunctionLibrary.h"

void ATPSWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	// 시작할 때 UI 정보 업데이트
	if (EventSystem)
	{
		EventSystem->OnAmmoChange.Broadcast(WeaponContext.CurrentAmmo, WeaponContext.MaxAmmo);
	}

	// 스탯 변경 델리게이트 바인딩
	auto GameplayEventInterface = Cast<ITPSEventComponentInterface>(GetOwner());
	if (GameplayEventInterface)
	{
		OnFieldChangedHandle = GameplayEventInterface->GetEventComponent()->OnWeaponFieldChangeEvent.AddUObject(this, &ATPSWeaponBase::ChangeFieldStatByValue);
	}
}

void ATPSWeaponBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// 스탯 변경 델리게이트 제거
	auto GameplayEventInterface = Cast<ITPSEventComponentInterface>(GetOwner());
	if (GameplayEventInterface)
	{
		GameplayEventInterface->GetEventComponent()->OnWeaponFieldChangeEvent.Remove(OnFieldChangedHandle);
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

	if (Character->IsLocallyControlled())
	{
		WeaponContext.CurrentAmmo -= WeaponContext.RequireAmmo;
	}

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

		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = GetInstigator();

		// 총알 클래스 생성
		auto Projectile = GetWorld()->SpawnActor<ATPSProjectileBase>(
			ProjectileList[WeaponContext.CurrentBullet],
			MuzzleLocation,
			ShotRotation,
			SpawnParams
		);

		// 총알 구조체가 만들어지면 내부 설정
		if (Projectile)
		{
			Projectile->Damage = WeaponContext.Damage;
			Projectile->UltiGaugeRatio = WeaponContext.UltiGaugeRatio;
		}

		// 발사 이펙트 생성
		ShotRotation.Pitch -= 90.0f;
		if (WeaponContext.MuzzleEffect)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				GetWorld(),
				WeaponContext.MuzzleEffect,
				GetActorLocation(),
				ShotRotation,
				FVector(1.f),
				true,
				true
			);
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

		WeaponContext.MuzzleEffect = WeaponData->MuzzleEffect;
	}
}

FWeaponContext ATPSWeaponBase::GetWeaponContext() const
{
	return WeaponContext;
}

void ATPSWeaponBase::ChangeFieldStatByValue(FName FieldName, float Value)
{
	// 1) 클래스 내부에서 FieldName을 가진 FProperty 찾기
	FProperty* FoundProperty = GetClass()->FindPropertyByName(FieldName);
	if (FoundProperty)
	{
		if (FFloatProperty* FloatProp = CastField<FFloatProperty>(FoundProperty))
		{
			float NewValue = FloatProp->GetPropertyValue_InContainer(this) + Value;

			FloatProp->SetPropertyValue_InContainer(this, NewValue);
			return;
		}
	}
	// 2) FDroneSkillContext 내부에서 FieldName을 가진 FProperty 찾기
	UScriptStruct* ContextStruct = FWeaponContext::StaticStruct();
	FProperty* ContextProp = ContextStruct->FindPropertyByName(FieldName);
	if (ContextProp)
	{
		if (FFloatProperty* FloatProp = CastField<FFloatProperty>(ContextProp))
		{
			// 현재 클래스의 WeaponContext 멤버 메모리 가져오기
			void* WeaponContextAddr = FindFieldChecked<FStructProperty>(GetClass(), TEXT("WeaponContext"))
				->ContainerPtrToValuePtr<void>(this);

			// 현재 값
			float CurrentValue = FloatProp->GetPropertyValue_InContainer(WeaponContextAddr);
			float NewValue = CurrentValue + Value;

			// 수정
			FloatProp->SetPropertyValue_InContainer(WeaponContextAddr, NewValue);
			return;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No matching field named %s found in class or SkillContext"), *FieldName.ToString());
	}
}

void ATPSWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPSWeaponBase, WeaponData);
	DOREPLIFETIME(ATPSWeaponBase, bCanFire);
	DOREPLIFETIME(ATPSWeaponBase, bIsReloading);
	DOREPLIFETIME(ATPSWeaponBase, WeaponContext);
}
