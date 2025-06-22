// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/DroneAbility/TPSDroneMoveToGrenade.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"

UTPSDroneMoveToGrenade::UTPSDroneMoveToGrenade()
{
	AbilityName = FText::FromString(TEXT("Move to Explosion"));
	AbilityDescription = FText::FromString(TEXT("Drone move where Grenade Hit"));
}

void UTPSDroneMoveToGrenade::InitializeDroneAbility(FDroneSkillContext& SkillContext)
{
	Super::InitializeDroneAbility(SkillContext);
}

void UTPSDroneMoveToGrenade::ApplyAbility()
{

}

void UTPSDroneMoveToGrenade::CancelAbility()
{
	GetOwnerEventComponent()->OnSpAttackHitEvent.Remove(DelegateHandle);
}

void UTPSDroneMoveToGrenade::InitializeAbilityEvent()
{
	GetOwnerEventComponent()->OnSpAttackHitEvent.AddUObject(this, &UTPSDroneMoveToGrenade::ApplyAbility);
}
