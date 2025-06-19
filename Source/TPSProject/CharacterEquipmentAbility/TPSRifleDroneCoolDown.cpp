// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSRifleDroneCoolDown.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"

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
			TEXT("Apply drone cool down")  // 출력할 메시지
		);
	}
}

void UTPSRifleDroneCoolDown::CancelAbility()
{
	GetOwnerEventComponent()->OnAttackHitEvent.Remove(DelegateHandle);
}

void UTPSRifleDroneCoolDown::InitializeAbilityEvent()
{
	DelegateHandle = GetOwnerEventComponent()->OnAttackHitEvent.AddUObject(this, &UTPSRifleDroneCoolDown::ApplyAbility);
}
