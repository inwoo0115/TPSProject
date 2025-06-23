// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/DroneAbility/TPSDroneGainUltiGauge.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"

UTPSDroneGainUltiGauge::UTPSDroneGainUltiGauge()
{
	AbilityName = FText::FromString(TEXT("Additional Ulti Guage"));

	AbilityDescription = FText::FromString(TEXT("Add 30% Ultimate Guage"));
}

void UTPSDroneGainUltiGauge::InitializeDroneAbility(FDroneSkillContext& SkillContext)
{
	Super::InitializeDroneAbility(SkillContext);
}

void UTPSDroneGainUltiGauge::ApplyAbilityWithLocation(FVector Location)
{
	AActor* Owner = Cast<AActor>(GetOuter());
	if (Owner && Owner->HasAuthority())
	{
		GetOwnerEventComponent()->OnUltiGaugeUpdateEvent.Broadcast(30.0f);

	}
	else
	{
		ServerRPCApplyAbility();
	}
}

void UTPSDroneGainUltiGauge::CancelAbility()
{
	GetOwnerEventComponent()->OnDroneCastEvent.Remove(DelegateHandle);
}

void UTPSDroneGainUltiGauge::InitializeAbilityEvent()
{
	DelegateHandle = GetOwnerEventComponent()->OnDroneCastEvent.AddUObject(this, &UTPSDroneGainUltiGauge::ApplyAbilityWithLocation);
}

void UTPSDroneGainUltiGauge::ServerRPCApplyAbility_Implementation()
{
	GetOwnerEventComponent()->OnUltiGaugeUpdateEvent.Broadcast(30.0f);
}
