// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterEquipment/TPSAbilityEquipmentBase.h"
#include "TPSEquipmentData.generated.h"

USTRUCT(BlueprintType)
struct FTPSEquipmentData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATPSAbilityEquipmentBase> EquipmentClass;
};