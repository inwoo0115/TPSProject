// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSSkillComponentBase.h"
#include "CharacterEquipment/TPSAbilityEquipmentBase.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"

UTPSSkillComponentBase::UTPSSkillComponentBase()
{
	// �����ڰ� Replicated �Ǿ��ִ��� Ȯ�� �� ����
	SetIsReplicatedByDefault(true);
}

void UTPSSkillComponentBase::Equip(TSubclassOf<ATPSAbilityEquipmentBase> EquipmentClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
	if (!GetOwner()->HasAuthority())
	{
		ServerRPCEquip(EquipmentClass, Ability1, Ability2, Ability3);
		return;
	}

	if (Equipment)
	{
		Equipment->Destroy();
	}

	UWorld* World = GetWorld();
	if (World && EquipmentClass)
	{
		// ��� ����
		FActorSpawnParameters Params;
		Params.Owner = GetOwner();
		Params.Instigator = GetOwner()->GetInstigator();
		Equipment = World->SpawnActor<ATPSAbilityEquipmentBase>(EquipmentClass, Params);

		// ��� �ʱ�ȭ
		Equipment->InitializeComponent(this);
		Equipment->InitializeAbilityListFromInventory();
		Equipment->InitializeAbilitiesFromDataAsset(Ability1, Ability2, Ability3);
		Equipment->InitializeAbilities();

		// ���� ��ġ �Ҵ�
		ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
		if (OwnerCharacter && Equipment)
		{
			USkeletalMeshComponent* MeshComp = OwnerCharacter->GetMesh();
			if (MeshComp)
			{
				Equipment->AttachToComponent(
					MeshComp,
					FAttachmentTransformRules::SnapToTargetNotIncludingScale,
					FName("Muzzle_02")
				);
			}
		}
	}
}

void UTPSSkillComponentBase::CastSkill()
{
}

void UTPSSkillComponentBase::LaunchSkill()
{
}

bool UTPSSkillComponentBase::GetCanCastSkill()
{
	return true;
}

void UTPSSkillComponentBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTPSSkillComponentBase, Equipment);
}

void UTPSSkillComponentBase::ServerRPCEquip_Implementation(TSubclassOf<ATPSAbilityEquipmentBase> EquipmentClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
	Equip(EquipmentClass, Ability1, Ability2, Ability3);
}
