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

	//MulticastRPCApplyAbility(Location);
	AActor* OwnerActor = Cast<AActor>(GetOuter());
	if (OwnerActor && OwnerActor->HasAuthority())
	{
		ApplyNuclearDamage(Location);
		MulticastRPCApplyAbility(Location);
	}
	
	if (OwnerActor && !OwnerActor->HasAuthority())
	{
		ServerRPCApplyAbility(Location);
	}

}

void UTPSUltiAddNuclear::ApplyNuclearDamage(FVector Location)
{
	// 이 위치를 기준으로 범위 데미지

	// 10초 후 발동
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		[this, Location]() // 람다 캡쳐
		{
			// 반드시 GetWorld() 유효성 검사
			if (!GetWorld()) return;

			UGameplayStatics::ApplyRadialDamage(
				GetWorld(),
				300.0f,
				Location,
				2000.0f,
				nullptr,               // 기본 DamageType
				TArray<AActor*>(),     // 무시할 액터들
				Cast<AActor>(GetOuter()),
				Cast<AActor>(GetOuter())->GetInstigatorController(),
				true,
				ECC_Pawn
			);
		},
		10.0f,     // 딜레이 초 단위
		false      // 반복하지 않음
	);

}

void UTPSUltiAddNuclear::ServerRPCApplyAbility_Implementation(FVector Location)
{
	MulticastRPCApplyAbility(Location);
	ApplyNuclearDamage(Location);
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
}

void UTPSUltiAddNuclear::InitializeAbilityEvent()
{
	DelegateHandle = GetOwnerEventComponent()->OnUltimateCastEvent.AddUObject(this, &UTPSUltiAddNuclear::ApplyAbilityWithLocation);

}