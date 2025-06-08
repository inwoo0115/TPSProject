// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleUltiGaugeBoost.h"
#include "CharacterComponent/TPSWeaponComponent.h"

void UTPSRifleUltiGaugeBoost::InitializeAbility(UActorComponent* InitializeComponent)
{
	UTPSWeaponComponent* WeaponComponent = Cast<UTPSWeaponComponent>(InitializeComponent);
	if (WeaponComponent)
	{
		WeaponComponent->EquippedWeapon->UltiGaugeRatio += 0.1f;
		CachedComponent = WeaponComponent;
	}
}
