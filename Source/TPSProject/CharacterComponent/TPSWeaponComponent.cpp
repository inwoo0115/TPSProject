// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSWeaponComponent.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "TPSGameplayEventSystem.h"
#include "GameFramework/Character.h"

void UTPSWeaponComponent::EquipWeapon(TSubclassOf<ATPSWeaponBase> WeaponClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
	if (EquippedWeapon)
	{
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
	return EquippedWeapon->bCanFire;
}

