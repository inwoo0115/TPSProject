// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TPSAnimMontageData.generated.h"

UENUM(BlueprintType)
enum class EMontageType : uint8
{
	Attack UMETA(DisplayName = "Attack"),
	RopeAction UMETA(DisplayName = "RopeAction"),
	SpAttack UMETA(DisplayName = "SpAttack")
};

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSAnimMontageData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = AninMontage)
	TMap<EMontageType, TObjectPtr<UAnimMontage>> AnimMontages;
};