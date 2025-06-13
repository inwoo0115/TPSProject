// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleDroneCoolDown.h"
#include "CharacterEquipment/TPSWeaponBase.h"

UTPSRifleDroneCoolDown::UTPSRifleDroneCoolDown()
{
	AbilityName = FText::FromString(TEXT("More Droner"));
	AbilityDescription = FText::FromString(TEXT("Cooldown Drone Skill when attack"));
}

void UTPSRifleDroneCoolDown::InitializeWeaponAbility(FWeaponContext& WeaponContext)
{
	Super::InitializeWeaponAbility(WeaponContext);

	UE_LOG(LogTemp, Warning, TEXT("Init drone"));
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
	UE_LOG(LogTemp, Log, TEXT("Broad cast"));
}
