// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSWeaponComponent.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "TPSGameplayEventSystem.h"
#include "GameFramework/Character.h"

UTPSWeaponComponent::UTPSWeaponComponent()
{
	// �����ڰ� Replicated �Ǿ��ִ��� Ȯ�� �� ����
	SetIsReplicatedByDefault(true);
}

void UTPSWeaponComponent::EquipWeapon(TSubclassOf<ATPSWeaponBase> WeaponClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
	if (EquippedWeapon)
	{
		// ��������Ʈ �ʱ�ȭ
		OnStopFire.Clear();
		OnBulletHit.Clear();

		// ���� ���� ���� ����
		EquippedWeapon->Destroy();
	}

	UWorld* World = GetWorld();
	if (World && WeaponClass)
	{
		// ���� ����
		EquippedWeapon = World->SpawnActor<ATPSWeaponBase>(WeaponClass);

		// ���� �ʱ�ȭ
		EquippedWeapon->InitializeComponentAndEventSystem(this, EventSystem);
		EquippedWeapon->InitializeAbilitiesFromDataAsset(Ability1, Ability2, Ability3);
		EquippedWeapon->InitializeAbilities();

		// ���� ��ġ �Ҵ�
		ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
		if (OwnerCharacter && EquippedWeapon)
		{
			USkeletalMeshComponent* MeshComp = OwnerCharacter->GetMesh();
			if (MeshComp)
			{
				EquippedWeapon->AttachToComponent(
					MeshComp,
					FAttachmentTransformRules::SnapToTargetNotIncludingScale,
					FName("Muzzle_01")
				);
			}
		}
	}

	// ���� ���� ���� ��Ƽ ĳ��Ʈ
	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if (OwnerPawn->HasAuthority())
	{
		MulticastRPCEquipWeapon(WeaponClass, Ability1, Ability2, Ability3);
	}
	else if (OwnerPawn->IsLocallyControlled())
	{
		ServerRPCEquipWeapon(WeaponClass, Ability1, Ability2, Ability3);
	}
}

void UTPSWeaponComponent::Initialize(UTPSGameplayEventSystem* InputEventSystem)
{
	EventSystem = InputEventSystem;
}

void UTPSWeaponComponent::FireWeapon()
{
	EquippedWeapon->Fire();
}

void UTPSWeaponComponent::LaunchWeapon()
{
	EquippedWeapon->Launch();
}

void UTPSWeaponComponent::ReleaseWeapon()
{
	EquippedWeapon->Release();
}

void UTPSWeaponComponent::ReloadWeapon()
{
	EquippedWeapon->Reload();
}

void UTPSWeaponComponent::EffectWeapon()
{
	EquippedWeapon->Effect();
}

bool UTPSWeaponComponent::GetCanLaunchWeapon()
{
	return EquippedWeapon->CanFire();
}

bool UTPSWeaponComponent::GetCanReloadWeapon()
{
	return EquippedWeapon->CanReload();
}

void UTPSWeaponComponent::ServerRPCEquipWeapon_Implementation(TSubclassOf<ATPSWeaponBase> WeaponClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
	EquipWeapon(WeaponClass, Ability1, Ability2, Ability3);
	MulticastRPCEquipWeapon(WeaponClass, Ability1, Ability2, Ability3);
}

void UTPSWeaponComponent::MulticastRPCEquipWeapon_Implementation(TSubclassOf<ATPSWeaponBase> WeaponClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if (!(OwnerPawn->IsLocallyControlled()) && !(GetOwner()->HasAuthority()))
	{
		EquipWeapon(WeaponClass, Ability1, Ability2, Ability3);
	}
}
