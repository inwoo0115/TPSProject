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
	SpAttack UMETA(DisplayName = "SpAttack"),
	Reload UMETA(DisplayName = "Reload"),
	Ultimate UMETA(DisplayName = "Ultimate")
};

UENUM(BlueprintType)
enum class EMontagePriority : uint8
{
	// ���� �켱�� ���� ���� ����
	Low	UMETA(DisplayName = "Low"),

	// ���� �켱�� ���� ���� �Ұ�
	Medium UMETA(DisplayName = "Medium"),

	// ���� �켱�� ���� ���� �Ұ�
	High UMETA(DisplayName = "High")
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

	UPROPERTY(EditAnywhere, Category = AninMontage)
	TMap<TObjectPtr<UAnimMontage>, EMontagePriority> AnimMontagePriority;
};