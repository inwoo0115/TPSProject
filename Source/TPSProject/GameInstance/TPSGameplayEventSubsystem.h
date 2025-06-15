// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TPSGameplayEventSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHitEvent);

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChange, int32 /*Current*/, int32 /*Max*/);

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCoolTimeChange, float /*Current*/, float /*Max*/);

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSGameplayEventSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

	// Attack Event
	FOnHitEvent OnHitEvent;

	// HUD Event
	FOnStatChange OnHPChange;

	FOnStatChange OnAmmoChange;

	FOnStatChange OnUltimateGaugeChange;

	FOnCoolTimeChange OnDroneCoolTimeChange;
	
	FOnCoolTimeChange OnSpAttackCoolTimeChange;

	// 발사체 히트 이벤트
	void BroadcastHitEvent();
};
