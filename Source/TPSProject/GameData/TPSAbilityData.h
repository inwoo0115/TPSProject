// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSAbilityData.generated.h"

USTRUCT(BlueprintType)
struct FTPSAbilityData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UTPSEquipmentAbilityBase> AbilityClass;
};