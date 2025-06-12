// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleDroneCoolDown.h"
#include "CharacterEquipment/TPSWeaponBase.h"

UTPSRifleDroneCoolDown::UTPSRifleDroneCoolDown()
{
	AbilityName = FText::FromString(TEXT("More Droner"));
	AbilityDescription = FText::FromString(TEXT("Cooldown Drone Skill when attack"));
}

void UTPSRifleDroneCoolDown::InitializeWeaponAbility(UTPSGameplayEventSystem* InitEventSystem, FWeaponContext& WeaponContext)
{
	Super::InitializeWeaponAbility(InitEventSystem, WeaponContext);

	//EventSystem->OnBulletHit.AddDynamic();
}

void UTPSRifleDroneCoolDown::ApplyAbility()
{
	//CachedComponent->EventSystem
	//drone cool down
	// CachedComponent->EventSystem->OnStatChanged.Broadcast();
}
