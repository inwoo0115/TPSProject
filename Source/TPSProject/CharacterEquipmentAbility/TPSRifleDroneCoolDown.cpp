// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleDroneCoolDown.h"
#include "CharacterComponent/TPSWeaponComponent.h"

void UTPSRifleDroneCoolDown::InitializeAbility(UActorComponent* InitializeComponent)
{
	UTPSWeaponComponent* WeaponComponent = Cast<UTPSWeaponComponent>(InitializeComponent);
	if (WeaponComponent)
	{
		WeaponComponent->OnBulletHit.AddDynamic(this, &UTPSRifleDroneCoolDown::ApplyAbility);
		CachedComponent = WeaponComponent;
	}
}

void UTPSRifleDroneCoolDown::ApplyAbility()
{
	//CachedComponent->EventSystem
	//drone cool down

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,                         // Key: -1�̸� �Ź� �� �޽���
			5.0f,                       // Duration in seconds
			FColor::Green,              // �ؽ�Ʈ ����
			TEXT("Drone Cool Down Apply") // �޽��� ����
		);
	}
}
