// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/SpAttackAbility/TPSGrenadeAddImpulse.h"
#include "CharacterEquipment/TPSSpAttackSkillBase.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"
#include "GameFramework/Character.h"
#include "Engine/OverlapResult.h"


UTPSGrenadeAddImpulse::UTPSGrenadeAddImpulse()
{
	AbilityName = FText::FromString(TEXT("Impulse Grenade"));
	AbilityDescription = FText::FromString(TEXT("Add Impulse to Center Location of Explosion"));

    AbilityType = EAbilityType::SpAttackAbility;

}

void UTPSGrenadeAddImpulse::InitializeSpAttackAbility(FSpAttackSkillContext& SkillContext)
{
	Super::InitializeSpAttackAbility(SkillContext);
}

void UTPSGrenadeAddImpulse::CancelAbility()
{
	GetOwnerEventComponent()->OnSpAttackHitEvent.Remove(DelegateHandle);
}

void  UTPSGrenadeAddImpulse::ApplyAbilityWithLocation(FVector Location)
{
    TArray<FOverlapResult> Overlaps;
    FCollisionShape Sphere = FCollisionShape::MakeSphere(500.0f);

    if (GetWorld()->OverlapMultiByChannel(Overlaps, Location, FQuat::Identity, ECC_Pawn, Sphere))
    {
        for (auto& Hit : Overlaps)
        {
            ACharacter* Char = Cast<ACharacter>(Hit.GetActor());
            if (Char)
            {
                FVector LaunchDir = (Char->GetActorLocation() - Location).GetSafeNormal();
                Char->LaunchCharacter(LaunchDir * 1000, true, true);
            }
        }
    }
}


void UTPSGrenadeAddImpulse::InitializeAbilityEvent()
{
	DelegateHandle = GetOwnerEventComponent()->OnSpAttackHitEvent.AddUObject(this, &UTPSGrenadeAddImpulse::ApplyAbilityWithLocation);
}
