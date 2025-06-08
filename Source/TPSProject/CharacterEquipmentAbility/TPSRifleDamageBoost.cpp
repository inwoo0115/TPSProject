// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleDamageBoost.h"
#include "CharacterEquipment/TPSBasicRifle.h"
#include "CharacterComponent/TPSWeaponComponent.h"
#include "CharacterComponent/TPSGameplayEventSystem.h"

void UTPSRifleDamageBoost::InitializeAbility(UActorComponent* InitializeComponent)
{
	UTPSWeaponComponent* WeaponComponent = Cast<UTPSWeaponComponent>(InitializeComponent);
	if (WeaponComponent)
	{
		WeaponComponent->EquippedWeapon->Damage += 20.0f;
		CachedComponent = WeaponComponent;
	}
}
