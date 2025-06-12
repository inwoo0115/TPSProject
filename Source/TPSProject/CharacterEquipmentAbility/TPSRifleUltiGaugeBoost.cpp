// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleUltiGaugeBoost.h"
#include "CharacterComponent/TPSWeaponComponent.h"

UTPSRifleUltiGaugeBoost::UTPSRifleUltiGaugeBoost()
{
	AbilityName = FText::FromString(TEXT("U.R.F Mode"));
	AbilityDescription = FText::FromString(TEXT("Get Additional Ultimate Gauege"));
}

void UTPSRifleUltiGaugeBoost::InitializeAbility(UTPSGameplayEventSystem* InitEventSystem, FWeaponContext& WeaponContext)
{
	Super::InitializeAbility(InitEventSystem, WeaponContext);

	WeaponContext.UltiGaugeRatio += 0.1f;
}
