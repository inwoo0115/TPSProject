// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/SpAttackAbility/TPSGrenadeAddBulletDamage.h"
#include "CharacterEquipment/TPSSpAttackSkillBase.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"

UTPSGrenadeAddBulletDamage::UTPSGrenadeAddBulletDamage()
{
	AbilityName = FText::FromString(TEXT("Add Bullet Damage"));
	AbilityDescription = FText::FromString(TEXT("Add Additional Damage on Weapon Attack for 5 seconds"));

    AbilityType = EAbilityType::SpAttackAbility;

}

void UTPSGrenadeAddBulletDamage::InitializeSpAttackAbility(FSpAttackSkillContext& SkillContext)
{
	Super::InitializeSpAttackAbility(SkillContext);
}

void UTPSGrenadeAddBulletDamage::ApplyAbilityWithLocation(FVector Location)
{
    AActor* Owner = Cast<AActor>(GetOuter());
    if (Owner && Owner->HasAuthority())
    {
        GetOwnerEventComponent()->OnWeaponFieldChangeEvent.Broadcast(FName(TEXT("Damage")), 10.0f);

        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(
            TimerHandle,
            [this]()
            {
                if (GetOwnerEventComponent())
                {
                    GetOwnerEventComponent()->OnWeaponFieldChangeEvent.Broadcast(FName(TEXT("Damage")), -10.0f);
                }
            },
            5.0f,
            false // 단발성 호출
        );
    }
}

void UTPSGrenadeAddBulletDamage::CancelAbility()
{
	GetOwnerEventComponent()->OnSpAttackHitEvent.Remove(DelegateHandle);
}

void UTPSGrenadeAddBulletDamage::InitializeAbilityEvent()
{
	DelegateHandle = GetOwnerEventComponent()->OnSpAttackHitEvent.AddUObject(this, &UTPSGrenadeAddBulletDamage::ApplyAbilityWithLocation);
}
