// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSWeaponComponent.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UTPSWeaponComponent::UTPSWeaponComponent()
{
	// 소유자가 Replicated 되어있는지 확인 후 변경
	SetIsReplicatedByDefault(true);
}

void UTPSWeaponComponent::EquipWeapon(TSubclassOf<ATPSWeaponBase> WeaponClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
	if (!GetOwner()->HasAuthority())
	{
		ServerRPCEquipWeapon(WeaponClass, Ability1, Ability2, Ability3);
		return;
	}

	if (EquippedWeapon)
	{
		EquippedWeapon->ClearAbilityDelegates();
		// 기존 무기 설정 제거
		EquippedWeapon->Destroy();
	}

	UWorld* World = GetWorld();
	if (World && WeaponClass)
	{
		// 무기 장착
		EquippedWeapon = World->SpawnActor<ATPSWeaponBase>(WeaponClass);

		// 무기 초기화
		EquippedWeapon->InitializeComponent(this);
		EquippedWeapon->InitializeAbilitiesFromDataAsset(Ability1, Ability2, Ability3);
		EquippedWeapon->InitializeAbilities();

		// 소켓 위치 할당
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

void UTPSWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTPSWeaponComponent, EquippedWeapon);
}

void UTPSWeaponComponent::ServerRPCEquipWeapon_Implementation(TSubclassOf<ATPSWeaponBase> WeaponClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
	EquipWeapon(WeaponClass, Ability1, Ability2, Ability3);
}
