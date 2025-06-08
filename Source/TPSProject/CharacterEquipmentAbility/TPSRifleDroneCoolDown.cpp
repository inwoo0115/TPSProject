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
			-1,                         // Key: -1이면 매번 새 메시지
			5.0f,                       // Duration in seconds
			FColor::Green,              // 텍스트 색상
			TEXT("Drone Cool Down Apply") // 메시지 내용
		);
	}
}
