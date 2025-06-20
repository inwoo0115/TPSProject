// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSUltimateComponent.h"
#include "CharacterEquipment/TPSUltimateSkillBase.h"

void UTPSUltimateComponent::Equip(TSubclassOf<ATPSAbilityEquipmentBase> EquipmentClass, EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
	if (!GetOwner()->HasAuthority())
	{
		ServerRPCEquip(EquipmentClass, Ability1, Ability2, Ability3);
		return;
	}

	if (Equipment)
	{
		// 기존 장비 설정 제거
		Equipment->ClearAbilityDelegates();
		auto UltimateEquipment = Cast<ATPSUltimateSkillBase>(Equipment);
		if (UltimateEquipment)
		{
			UltimateEquipment->ClearUpdateDelegate();
		}
		Equipment->Destroy();
	}

	UWorld* World = GetWorld();
	if (World && EquipmentClass)
	{
		// 장비 장착
		FActorSpawnParameters Params;
		Params.Owner = GetOwner();
		Equipment = World->SpawnActor<ATPSAbilityEquipmentBase>(EquipmentClass, Params);

		// 장비 초기화
		Equipment->InitializeComponent(this);
		Equipment->InitializeAbilitiesFromDataAsset(Ability1, Ability2, Ability3);
		Equipment->InitializeAbilities();

		// 소켓 위치 할당
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

void UTPSUltimateComponent::ShowCastUI()
{
    auto UltiEquipment = Cast<ATPSUltimateSkillBase>(Equipment);
    if (UltiEquipment)
    {
        UltiEquipment->ShowUI();
    }
}

void UTPSUltimateComponent::CastSkill()
{
    auto UltiEquipment = Cast<ATPSUltimateSkillBase>(Equipment);
    if (UltiEquipment)
    {
        UltiEquipment->CastSkill();
    }
}

void UTPSUltimateComponent::LaunchSkill()
{
    auto UltiEquipment = Cast<ATPSUltimateSkillBase>(Equipment);
    if (UltiEquipment)
    {
        UltiEquipment->LaunchSkill();
    }
}

bool UTPSUltimateComponent::GetCanCastSkill()
{
    auto UltiEquipment = Cast<ATPSUltimateSkillBase>(Equipment);
    if (UltiEquipment)
    {
        return UltiEquipment->GetCanCast();
    }

    return false;
}
