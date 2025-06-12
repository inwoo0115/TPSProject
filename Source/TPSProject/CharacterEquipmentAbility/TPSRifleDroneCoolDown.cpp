// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleDroneCoolDown.h"
#include "CharacterComponent/TPSWeaponComponent.h"

UTPSRifleDroneCoolDown::UTPSRifleDroneCoolDown()
{
	AbilityName = FText::FromString(TEXT("More Droner"));
	AbilityDescription = FText::FromString(TEXT("Cooldown Drone Skill when attack"));
}

void UTPSRifleDroneCoolDown::InitializeAbility(UTPSGameplayEventSystem* InitEventSystem, FWeaponContext& WeaponContext)
{
	Super::InitializeAbility(InitEventSystem, WeaponContext);

	//EventSystem->OnBulletHit.AddDynamic();
}

void UTPSRifleDroneCoolDown::ApplyAbility()
{
	//CachedComponent->EventSystem
	//drone cool down
	// CachedComponent->EventSystem->OnStatChanged.Broadcast();
}
