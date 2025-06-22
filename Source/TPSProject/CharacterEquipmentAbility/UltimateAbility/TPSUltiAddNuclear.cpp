// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/UltimateAbility/TPSUltiAddNuclear.h"
#include "CharacterEquipment/TPSUltimateSkillBase.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

UTPSUltiAddNuclear::UTPSUltiAddNuclear()
{
	AbilityName = FText::FromString(TEXT("Nuclear"));
	AbilityDescription = FText::FromString(TEXT("Add Nuclear"));

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Explosion(TEXT("/Game/Sci-Fi_Starter_VFX_Pack_Niagara/Niagara/Explosion/NS_Explosion_BlackHole.NS_Explosion_BlackHole"));
	if (Explosion.Succeeded())
	{
		ExplosionEffect = Explosion.Object;
	}
}

void UTPSUltiAddNuclear::InitializeUltimateAbility(FUltimateSkillContext& SkillContext)
{
	Super::InitializeUltimateAbility(SkillContext);
}

void UTPSUltiAddNuclear::CancelAbility()
{
	GetOwnerEventComponent()->OnUltimateCastEvent.Remove(DelegateHandle);
}

void UTPSUltiAddNuclear::ApplyAbilityWithLocation(FVector Location)
{
	if (!ExplosionEffect) return;

    ServerRPCApplyAbility(Location);
}


void UTPSUltiAddNuclear::InitializeAbilityEvent()
{
	DelegateHandle = GetOwnerEventComponent()->OnUltimateCastEvent.AddUObject(this, &UTPSUltiAddNuclear::ApplyAbilityWithLocation);

}

void UTPSUltiAddNuclear::ApplyNuclearDamage(FVector Location, UNiagaraComponent* Effect)
{
    if (Effect)
    {
        if (Effect && !Effect->IsPendingKillEnabled())
        {
            Effect->DestroyComponent();
        }

        // 이 위치를 기준으로 범위 데미지
        UGameplayStatics::ApplyRadialDamage(
            GetWorld(),
            200.0f,
            Location,
            1000.0f,
            nullptr,               // 기본 DamageType
            TArray<AActor*>(),     // 무시할 액터들
            Cast<AActor>(GetOuter()),
            Cast<AActor>(GetOuter())->GetInstigatorController(),
            false
        );
    }
}

void UTPSUltiAddNuclear::ServerRPCApplyAbility_Implementation(FVector Location)
{
    MulticastRPCApplyAbility(Location);
}

void UTPSUltiAddNuclear::MulticastRPCApplyAbility_Implementation(FVector Location)
{
    UNiagaraComponent* SpawnedEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),
        ExplosionEffect,
        Location,
        FRotator::ZeroRotator,
        FVector(3.f), // 3배 크기
        true,         // auto destroy
        true          // auto activate
    );

    if (SpawnedEffect)
    {
        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(
            TimerHandle,
            [this, Location, SpawnedEffect]()  // this와 Location, SpawnedEffect 캡쳐
            {
                ApplyNuclearDamage(Location, SpawnedEffect);
            },
            10.f,  // 10초 후 소멸
            false
        );
    }
}
