// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TPSGameplayEventSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHitEvent);

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSGameplayEventSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

	FOnHitEvent OnHitEvent;

	void BroadcastHitEvent();
};
