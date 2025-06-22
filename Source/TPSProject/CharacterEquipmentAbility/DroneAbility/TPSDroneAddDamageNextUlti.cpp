// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/DroneAbility/TPSDroneAddDamageNextUlti.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"

UTPSDroneAddDamageNextUlti::UTPSDroneAddDamageNextUlti()
{
	AbilityName = FText::FromString(TEXT("Make Ulti Stronger"));
	AbilityDescription = FText::FromString(TEXT("Add More Damage to Ultimate in 3 second"));
}

void UTPSDroneAddDamageNextUlti::InitializeDroneAbility(FDroneSkillContext& SkillContext)
{
	Super::InitializeDroneAbility(SkillContext);
}

void UTPSDroneAddDamageNextUlti::ApplyAbility()
{
	GetOwnerEventComponent()->OnUltimateFieldChangeEvent.Broadcast(FName(TEXT("Damage")), 30.0f);

	FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle,
        [this]()
        {
            if (GetOwnerEventComponent())
            {
                GetOwnerEventComponent()->OnUltimateFieldChangeEvent.Broadcast(FName(TEXT("Damage")), -30.0f);
            }
        },
        3.0f,
        false // 단발성 호출
    );
}

void UTPSDroneAddDamageNextUlti::CancelAbility()
{
	GetOwnerEventComponent()->OnDroneCastEvent.Remove(DelegateHandle);
}

void UTPSDroneAddDamageNextUlti::InitializeAbilityEvent()
{
	GetOwnerEventComponent()->OnDroneCastEvent.AddUObject(this, &UTPSDroneAddDamageNextUlti::ApplyAbility);
}
