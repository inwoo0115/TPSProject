// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TPSGameplayEventSystem.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFieldChanged, FName /*FieldName*/, float /*NewStat*/);

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRequestDamageCalculation, FName /*FieldName*/, float& /*OutDamage*/);
/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSGameplayEventSystem : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FOnFieldChanged OnStatChanged;

	UPROPERTY()
	FOnRequestDamageCalculation OnRequestDamageCalculation;

	// Stat 변경 시 호출 이벤트
	void BroadCastOnStatChanged(FName FieldName, float NewStat);

	// Damage 계산 시 호출 이벤트
	float BroadCastOnDamageCalculation(FName FieldName);

};
