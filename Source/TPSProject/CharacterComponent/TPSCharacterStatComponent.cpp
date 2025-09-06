// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSCharacterStatComponent.h"
#include "Interface/TPSEventComponentInterface.h"
#include "GameInstance/TPSGameplayEventSubsystem.h"
#include "Net/UnrealNetwork.h"
#include "TPSGameplayEventComponent.h"

UTPSCharacterStatComponent::UTPSCharacterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentHP = 500;
	MaxHP = 500;
	Defensive = 10;

	SetIsReplicatedByDefault(true);
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

	// Delegate Bind
	auto EventComponent = Cast<ITPSEventComponentInterface>(GetOwner());
	if (EventComponent)
	{
		EventComponent->GetEventComponent()->OnHpChangeEvent.AddUObject(this, &UTPSCharacterStatComponent::UpdateHp);
	}
}

void UTPSCharacterStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTPSCharacterStatComponent, CurrentHP);
	DOREPLIFETIME(UTPSCharacterStatComponent, MaxHP);
	DOREPLIFETIME(UTPSCharacterStatComponent, Defensive);
	DOREPLIFETIME(UTPSCharacterStatComponent, Damage);
}

float UTPSCharacterStatComponent::CaculateDamage(float TakeDamage)
{
	float DamageResult = TakeDamage * (100 / (100 + Defensive));

	if (CurrentHP - DamageResult < 0)
	{
		CurrentHP = 0;
	}
	else
	{
		CurrentHP -= DamageResult;
	}

	APawn* PawnOwner = Cast<APawn>(GetOwner());

	if (PawnOwner && PawnOwner->IsLocallyControlled())
	{
		EventSystem->OnHPChange.Broadcast(CurrentHP, MaxHP);
	}

	return DamageResult;
}

void UTPSCharacterStatComponent::UpdateHp(float HpDelta)
{
	if (CurrentHP + HpDelta < 0)
	{
		CurrentHP = 0;
	}
	else if (CurrentHP + HpDelta > MaxHP)
	{
		CurrentHP = MaxHP;
	}
	else
	{
		CurrentHP += HpDelta;
	}

	APawn* PawnOwner = Cast<APawn>(GetOwner());

	if (PawnOwner && PawnOwner->IsLocallyControlled())
	{
		EventSystem->OnHPChange.Broadcast(CurrentHP, MaxHP);
	}
}

void UTPSCharacterStatComponent::OnRep_CurrentHP()
{
	APawn* PawnOwner = Cast<APawn>(GetOwner());

	if (PawnOwner && PawnOwner->IsLocallyControlled())
	{
		EventSystem->OnHPChange.Broadcast(CurrentHP, MaxHP);
	}
}
