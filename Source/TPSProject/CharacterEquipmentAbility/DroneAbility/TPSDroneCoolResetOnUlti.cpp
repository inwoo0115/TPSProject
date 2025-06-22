// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/DroneAbility/TPSDroneCoolResetOnUlti.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"

UTPSDroneCoolResetOnUlti::UTPSDroneCoolResetOnUlti()
{
	AbilityName = FText::FromString(TEXT("Cool Reset"));

	AbilityDescription = FText::FromString(TEXT("CoolTime Reset by Casting Ultimate"));
}

void UTPSDroneCoolResetOnUlti::InitializeDroneAbility(FDroneSkillContext& SkillContext)
{
	Super::InitializeDroneAbility(SkillContext);
}

void UTPSDroneCoolResetOnUlti::ApplyAbility()
{
	GetOwnerEventComponent()->OnDroneFieldChangeEvent.Broadcast(FName(TEXT("CurrentCoolTime")), 100.0f);
}

void UTPSDroneCoolResetOnUlti::CancelAbility()
{
	GetOwnerEventComponent()->OnUltimateCastEvent.Remove(DelegateHandle);
}

void UTPSDroneCoolResetOnUlti::InitializeAbilityEvent()
{
	GetOwnerEventComponent()->OnUltimateCastEvent.AddUObject(this, &UTPSDroneCoolResetOnUlti::ApplyAbility);
}
