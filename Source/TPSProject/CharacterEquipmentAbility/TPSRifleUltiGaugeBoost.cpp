// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleUltiGaugeBoost.h"
#include "CharacterEquipment/TPSWeaponBase.h"

UTPSRifleUltiGaugeBoost::UTPSRifleUltiGaugeBoost()
{
	AbilityName = FText::FromString(TEXT("U.R.F Mode"));
	AbilityDescription = FText::FromString(TEXT("Get Additional Ultimate Gauege"));
}

void UTPSRifleUltiGaugeBoost::InitializeWeaponAbility(FWeaponContext& WeaponContext)
{
	Super::InitializeWeaponAbility(WeaponContext);

	WeaponContext.UltiGaugeRatio += 0.1f;
}
