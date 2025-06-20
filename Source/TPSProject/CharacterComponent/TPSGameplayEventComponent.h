// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSGameplayEventComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHitEvent);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStatChangeEvent, float);

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

	// Hp Change Event
	FOnStatChangeEvent OnHpChangeEvent;

	// Ulti Gauge Event
	FOnStatChangeEvent OnUltiGaugeUpdateEvent;

};
