// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TPSGameplayEventSystem.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFieldChanged, FName /*FieldName*/, float /*NewStat*/);

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSGameplayEventSystem : public UObject
{
	GENERATED_BODY()
	
public:

	FOnFieldChanged OnStatChanged;

	// Stat 변경 시 호출 이벤트
	void BroadCastOnStatChanged(FName FieldName, float NewStat);
};
