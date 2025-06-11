// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleAddLaserBullet.h"
#include "CharacterComponent/TPSWeaponComponent.h"
#include "CharacterEquipment/TPSBasicRifle.h"

UTPSRifleAddLaserBullet::UTPSRifleAddLaserBullet()
{
	AbilityName = FText::FromString(TEXT("LaserMode"));
	AbilityDescription = FText::FromString(TEXT("Change to Laser Bullet when Attack"));
}

void UTPSRifleAddLaserBullet::InitializeAbility(UActorComponent* InitializeComponent)
{
	UTPSWeaponComponent* WeaponComponent = Cast<UTPSWeaponComponent>(InitializeComponent);
	if (WeaponComponent)
	{
		auto Weapon = Cast<ATPSBasicRifle>(WeaponComponent->EquippedWeapon);
		if (Weapon)
		{
			WeaponComponent->OnBulletHit.AddDynamic(this, &UTPSRifleAddLaserBullet::ApplyAbility);
			Weapon->HasLaserMode = true;
		}
		CachedComponent = WeaponComponent;
	}
}

void UTPSRifleAddLaserBullet::ApplyAbility()
{
	//CachedComponent->EventSystem
	//drone cool down

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,                         // Key: -1이면 매번 새 메시지
			5.0f,                       // Duration in seconds
			FColor::Green,              // 텍스트 색상
			TEXT("Laser Bullet apply") // 메시지 내용
		);
	}
}
