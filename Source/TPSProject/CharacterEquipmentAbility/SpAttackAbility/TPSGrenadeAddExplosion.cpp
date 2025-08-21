// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/SpAttackAbility/TPSGrenadeAddExplosion.h"
#include "CharacterEquipment/TPSSpAttackSkillBase.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"

UTPSGrenadeAddExplosion::UTPSGrenadeAddExplosion()
{
	AbilityName = FText::FromString(TEXT("Explosions are Art"));
	AbilityDescription = FText::FromString(TEXT("More Explosion on Grenade Hit Location"));

    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Explosion(TEXT("/Game/Sci-Fi_Starter_VFX_Pack_Niagara/Niagara/Explosion/NS_Explosion_Grenade_2.NS_Explosion_Grenade_2"));
    if (Explosion.Succeeded())
    {
        ExplosionEffect = Explosion.Object;
    }

    AbilityType = EAbilityType::SpAttackAbility;
}

void UTPSGrenadeAddExplosion::InitializeSpAttackAbility(FSpAttackSkillContext& SkillContext)
{
	Super::InitializeSpAttackAbility(SkillContext);
}

void UTPSGrenadeAddExplosion::ApplyAbilityWithLocation(FVector Location)
{
	if (!ExplosionEffect) return;

    const int32 NumExplosions = FMath::RandRange(4, 5);  // 3~4개 폭발
    const float Radius = 600.f;                          // 폭발 퍼질 반경
    const float Damage = 20.f;                           // 폭발 데미지
    const float DamageRadius = 200.f;                    // 피해 반경

    for (int32 i = 0; i < NumExplosions; i++)
    {
        FVector RandomDir = UKismetMathLibrary::RandomUnitVector();
        float Distance = FMath::FRandRange(100.f, Radius);
        FVector SpawnLocation = Location + RandomDir * Distance;

        MulticastRPCApplyAbility(Location);

        // 이 위치를 기준으로 범위 데미지
        UGameplayStatics::ApplyRadialDamage(
            GetWorld(),
            Damage,
            SpawnLocation,
            DamageRadius,
            nullptr,               // 기본 DamageType
            TArray<AActor*>(),     // 무시할 액터들
            Cast<AActor>(GetOuter()),
            Cast<AActor>(GetOuter())->GetInstigatorController(),
            true,
            ECC_Pawn
        );
    }
}

void UTPSGrenadeAddExplosion::CancelAbility()
{
	GetOwnerEventComponent()->OnSpAttackHitEvent.Remove(DelegateHandle);
}

void UTPSGrenadeAddExplosion::InitializeAbilityEvent()
{
	DelegateHandle = GetOwnerEventComponent()->OnSpAttackHitEvent.AddUObject(this, &UTPSGrenadeAddExplosion::ApplyAbilityWithLocation);
}

void UTPSGrenadeAddExplosion::MulticastRPCApplyAbility_Implementation(FVector Location)
{
    // 나이아가라 폭발 소환
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),
        ExplosionEffect,
        Location,
        FRotator::ZeroRotator,
        FVector(1.f),
        true,  // auto destroy
        true
    );
}
