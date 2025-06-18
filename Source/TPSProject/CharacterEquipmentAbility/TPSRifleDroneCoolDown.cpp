// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleDroneCoolDown.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "GameInstance/TPSGameplayEventSubsystem.h"

UTPSRifleDroneCoolDown::UTPSRifleDroneCoolDown()
{
	AbilityName = FText::FromString(TEXT("More Droner"));
	AbilityDescription = FText::FromString(TEXT("Cooldown Drone Skill when attack"));
}

void UTPSRifleDroneCoolDown::InitializeWeaponAbility(FWeaponContext& WeaponContext)
{
	Super::InitializeWeaponAbility(WeaponContext);

}

void UTPSRifleDroneCoolDown::ApplyAbility()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,                         // Key (-1: 항상 새로운 메시지로)
			5.0f,                       // 화면에 표시되는 시간 (초)
			FColor::Green,              // 텍스트 색상
			);
	}
}

void UTPSRifleDroneCoolDown::CancelAbility()
{
	GetGameplayEventSubsystem()->OnHitEvent.Remove(DelegateHandle);
}

void UTPSRifleDroneCoolDown::InitializeAbilityEvent()
{
	DelegateHandle = GetGameplayEventSubsystem()->OnHitEvent.AddUObject(this, &UTPSRifleDroneCoolDown::ApplyAbility);
}
