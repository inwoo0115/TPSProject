// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/DroneAbility/TPSDroneCoolResetOnUlti.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"

UTPSDroneCoolResetOnUlti::UTPSDroneCoolResetOnUlti()
{
	AbilityName = FText::FromString(TEXT("Cool Reset"));

	AbilityDescription = FText::FromString(TEXT("CoolTime Reset by Casting Ultimate"));

	AbilityType = EAbilityType::DroneAbility;
}

void UTPSDroneCoolResetOnUlti::InitializeDroneAbility(FDroneSkillContext& SkillContext)
{
	Super::InitializeDroneAbility(SkillContext);
}

void UTPSDroneCoolResetOnUlti::ApplyAbilityWithLocation(FVector Location)
{
	GetOwnerEventComponent()->OnDroneFieldChangeEvent.Broadcast(FName(TEXT("CurrentCoolTime")), 100.0f);
}

void UTPSDroneCoolResetOnUlti::CancelAbility()
{
	GetOwnerEventComponent()->OnUltimateCastEvent.Remove(DelegateHandle);
}

void UTPSDroneCoolResetOnUlti::InitializeAbilityEvent()
{
	DelegateHandle = GetOwnerEventComponent()->OnUltimateCastEvent.AddUObject(this, &UTPSDroneCoolResetOnUlti::ApplyAbilityWithLocation);
}
