// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleDamageBoost.h"
#include "CharacterEquipment/TPSBasicRifle.h"
#include "CharacterComponent/TPSWeaponComponent.h"
#include "CharacterComponent/TPSGameplayEventSystem.h"

void UTPSRifleDamageBoost::InitializeAbility(UActorComponent* InitializeComponent)
{
	UTPSWeaponComponent* WeaponComponent = Cast<UTPSWeaponComponent>(InitializeComponent);
	if (InitializeComponent)
	{
		//WeaponComponent->EventSystem->BroadCastOnStatChanged(TEXT("Damage"), 120.0f);
		//WeaponComponent->EquippedWeapon->Damage = 120.0f;
		CachedComponent = WeaponComponent;
	}
}
