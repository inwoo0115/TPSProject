// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/DroneAbility/TPSDroneGainUltiGauge.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"

UTPSDroneGainUltiGauge::UTPSDroneGainUltiGauge()
{
	AbilityName = FText::FromString(TEXT("More Power"));

	AbilityDescription = FText::FromString(TEXT("Add 10 Damage or Heal per second"));
}

void UTPSDroneGainUltiGauge::InitializeDroneAbility(FDroneSkillContext& SkillContext)
{
	Super::InitializeDroneAbility(SkillContext);
}

void UTPSDroneGainUltiGauge::ApplyAbility()
{
	GetOwnerEventComponent()->OnUltimateFieldChangeEvent.Broadcast(FName(TEXT("CurrentGauge")), 10.0f);
}

void UTPSDroneGainUltiGauge::CancelAbility()
{
	GetOwnerEventComponent()->OnDroneCastEvent.Remove(DelegateHandle);
}

void UTPSDroneGainUltiGauge::InitializeAbilityEvent()
{
	DelegateHandle = GetOwnerEventComponent()->OnDroneCastEvent.AddUObject(this, &UTPSDroneGainUltiGauge::ApplyAbility);
}
