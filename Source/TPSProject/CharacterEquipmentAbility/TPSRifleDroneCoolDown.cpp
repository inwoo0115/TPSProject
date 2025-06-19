// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleDroneCoolDown.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"

UTPSRifleDroneCoolDown::UTPSRifleDroneCoolDown()
{
	AbilityName = FText::FromString(TEXT("More Droner"));
	AbilityDescription = FText::FromString(TEXT("Cooldown Drone Skill when attack"));
}

void UTPSRifleDroneCoolDown::InitializeWeaponAbility(FWeaponContext& WeaponContext)
{
	Super::InitializeWeaponAbility(WeaponContext);

}

void UTPSRifleDroneCoolDown::ApplyAbility()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,                         // Key (-1: �׻� ���ο� �޽�����)
			5.0f,                       // ȭ�鿡 ǥ�õǴ� �ð� (��)
			FColor::Green,              // �ؽ�Ʈ ����
			TEXT("Apply drone cool down")  // ����� �޽���
		);
	}
}

void UTPSRifleDroneCoolDown::CancelAbility()
{
	GetOwnerEventComponent()->OnAttackHitEvent.Remove(DelegateHandle);
}

void UTPSRifleDroneCoolDown::InitializeAbilityEvent()
{
	DelegateHandle = GetOwnerEventComponent()->OnAttackHitEvent.AddUObject(this, &UTPSRifleDroneCoolDown::ApplyAbility);
}
