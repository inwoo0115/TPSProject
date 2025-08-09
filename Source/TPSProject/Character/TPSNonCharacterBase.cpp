// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPSNonCharacterBase.h"
#include "Interface/TPSUltiGaugeInterface.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"
#include "Interface/TPSEventComponentInterface.h"
#include "Interface/TPSSetTargetInterface.h"
#include "Net/UnrealNetwork.h"
#include "AI/TPSAIController.h"


// Sets default values
ATPSNonCharacterBase::ATPSNonCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterName = FText::FromString(TEXT("Target"));

	// AI Controller 설정
	AIControllerClass = ATPSAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ATPSNonCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

float ATPSNonCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 데미지 판정은 서버에서만
	if (HasAuthority())
	{
		float DamageResult = CalculateDamage(DamageAmount);
		// 궁극기 게이지
		auto EventInterface = Cast<ITPSEventComponentInterface>(EventInstigator->GetPawn());
		if (EventInterface)
		{
			auto GaugeInterface = Cast<ITPSUltiGaugeInterface>(DamageCauser);
			if (GaugeInterface)
			{
				EventInterface->GetEventComponent()->OnUltiGaugeUpdateEvent.Broadcast(DamageResult * GaugeInterface->GetUltimateGaugeRatio());
			}
		}

		auto TargetInterface = Cast<ITPSSetTargetInterface>(EventInstigator);
		if (TargetInterface)
		{
			TargetInterface->SetTarget(this);
		}

		return DamageResult;
	}
	return 0.0f;
}

float ATPSNonCharacterBase::CalculateDamage(float Damage)
{
	if (CurrentHp - Damage < 0)
	{
		CurrentHp = 0;
	}
	else
	{
		CurrentHp -= Damage;
	}

	return Damage;
}

void ATPSNonCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPSNonCharacterBase, CurrentHp);
	DOREPLIFETIME(ATPSNonCharacterBase, MaxHp);
}

