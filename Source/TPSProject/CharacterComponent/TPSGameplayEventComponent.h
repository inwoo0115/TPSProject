// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSGameplayEventComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnHitEvent, FVector);

DECLARE_MULTICAST_DELEGATE(FOnCastEvent);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStatChangeEvent, float);

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFieldChangeEvent, FName /*Field*/, float /*Value*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UTPSGameplayEventComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTPSGameplayEventComponent();

	// Attack Event
	FOnHitEvent OnAttackHitEvent;

	// Sp Attack Event
	FOnHitEvent OnSpAttackHitEvent;

	// Drone Cast Event
	FOnCastEvent OnDroneCastEvent;

	// Ultimate Cast Event
	FOnCastEvent OnUltimateCastEvent;

	// Hp Change Event
	FOnStatChangeEvent OnHpChangeEvent;

	// Ulti Gauge Event
	FOnStatChangeEvent OnUltiGaugeUpdateEvent;

	//Field Change Event
	FOnFieldChangeEvent OnDroneFieldChangeEvent;

	FOnFieldChangeEvent OnUltimateFieldChangeEvent;

	FOnFieldChangeEvent OnWeaponFieldChangeEvent;

	FOnFieldChangeEvent OnSpAttackFieldChangeEvent;
};
