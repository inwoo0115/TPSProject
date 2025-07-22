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

	// ������ �� UI ���� ������Ʈ
	if (EventSystem)
	{
		EventSystem->OnAmmoChange.Broadcast(WeaponContext.CurrentAmmo, WeaponContext.MaxAmmo);
	}

	// ���� ���� ��������Ʈ ���ε�
	auto GameplayEventInterface = Cast<ITPSEventComponentInterface>(GetOwner());
	if (GameplayEventInterface)
	{
		OnFieldChangedHandle = GameplayEventInterface->GetEventComponent()->OnWeaponFieldChangeEvent.AddUObject(this, &ATPSWeaponBase::ChangeFieldStatByValue);
	}
}

void ATPSWeaponBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// ���� ���� ��������Ʈ ����
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

		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = GetInstigator();

		// �Ѿ� Ŭ���� ����
		auto Projectile = GetWorld()->SpawnActor<ATPSProjectileBase>(
			ProjectileList[WeaponContext.CurrentBullet],
			MuzzleLocation,
			ShotRotation,
			SpawnParams
		);

		// �Ѿ� ����ü�� ��������� ���� ����
		if (Projectile)
		{
			Projectile->Damage = WeaponContext.Damage;
			Projectile->UltiGaugeRatio = WeaponContext.UltiGaugeRatio;
		}

		// �߻� ����Ʈ ����
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
	// 1) Ŭ���� ���ο��� FieldName�� ���� FProperty ã��
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
	// 2) FDroneSkillContext ���ο��� FieldName�� ���� FProperty ã��
	UScriptStruct* ContextStruct = FWeaponContext::StaticStruct();
	FProperty* ContextProp = ContextStruct->FindPropertyByName(FieldName);
	if (ContextProp)
	{
		if (FFloatProperty* FloatProp = CastField<FFloatProperty>(ContextProp))
		{
			// ���� Ŭ������ WeaponContext ��� �޸� ��������
			void* WeaponContextAddr = FindFieldChecked<FStructProperty>(GetClass(), TEXT("WeaponContext"))
				->ContainerPtrToValuePtr<void>(this);

			// ���� ��
			float CurrentValue = FloatProp->GetPropertyValue_InContainer(WeaponContextAddr);
			float NewValue = CurrentValue + Value;

			// ����
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
