// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleMaxAmmoAdd.h"
#include "CharacterComponent/TPSWeaponComponent.h"

UTPSRifleMaxAmmoAdd::UTPSRifleMaxAmmoAdd()
{
	AbilityName = FText::FromString(TEXT("I Can do this All Day"));
	AbilityDescription = FText::FromString(TEXT("Add 50 Ammo"));
}

void UTPSRifleMaxAmmoAdd::InitializeAbility(UActorComponent* InitializeComponent)
{
	UTPSWeaponComponent* WeaponComponent = Cast<UTPSWeaponComponent>(InitializeComponent);
	if (WeaponComponent)
	{
		WeaponComponent->EquippedWeapon->MaxAmmo += 50;
		WeaponComponent->EquippedWeapon->CurrentAmmo += 50;
		CachedComponent = WeaponComponent;
	}
}
