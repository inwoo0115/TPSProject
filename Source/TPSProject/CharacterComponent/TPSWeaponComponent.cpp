// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSWeaponComponent.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "TPSGameplayEventSystem.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "GameFramework/Character.h"

void UTPSWeaponComponent::EquipWeapon(TSubclassOf<ATPSWeaponBase> WeaponClass)
{
	if (EquippedWeapon)
	{
		EquippedWeapon->Destroy();
	}

	UWorld* World = GetWorld();
	if (World && WeaponClass)
	{
		// ���� ����
		EquippedWeapon = World->SpawnActor<ATPSWeaponBase>(WeaponClass);

		// ���� �ʱ�ȭ
		EquippedWeapon->InitializeComponent(this);
		EquippedWeapon->InitializeAbilitiesFromDataAsset(EAbilityType::Group1Ability1, EAbilityType::Group2Ability1, EAbilityType::Group3Ability1);
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
}

void UTPSWeaponComponent::Initialize(UTPSGameplayEventSystem* InputEventSystem)
{
	EventSystem = InputEventSystem;
}

void UTPSWeaponComponent::FireWeapon()
{
	EquippedWeapon->Fire();
}

void UTPSWeaponComponent::ReleaseWeapon()
{
	EquippedWeapon->Release();
}

void UTPSWeaponComponent::ReloadWeapon()
{
	EquippedWeapon->Reload();
}

