// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSCharacterStatComponent.h"
#include "Interface/TPSEventComponentInterface.h"
#include "GameInstance/TPSGameplayEventSubsystem.h"

UTPSCharacterStatComponent::UTPSCharacterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentHP = 250;
	MaxHP = 250;
	Defensive = 1;
}

void UTPSCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// HP UI 업데이트 및 Event System 캐싱
	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (PawnOwner && PawnOwner->IsLocallyControlled())
	{
		auto GameplayEventSystem = PawnOwner->GetGameInstance()->GetSubsystem<UTPSGameplayEventSubsystem>();
		if (GameplayEventSystem)
		{
			EventSystem = GameplayEventSystem;
			
			EventSystem->OnHPChange.Broadcast(CurrentHP, MaxHP);
		}
	}


}


void UTPSCharacterStatComponent::GetDamageByField(FName FieldName, float& OutDamage)
{
	// FieldName 으로 맵에서 데미지 가져옴
	OutDamage *= Damage;
}
