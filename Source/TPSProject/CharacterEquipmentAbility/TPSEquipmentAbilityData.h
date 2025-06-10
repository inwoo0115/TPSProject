// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TPSEquipmentAbilityBase.h"
#include "TPSEquipmentAbilityData.generated.h"

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	None		   UMETA(DisplayName = "None"),
	Group1Ability1 UMETA(DisplayName = "Group1Ability1"),
	Group1Ability2 UMETA(DisplayName = "Group1Ability2"),
	Group2Ability1 UMETA(DisplayName = "Group2Ability1"),
	Group2Ability2 UMETA(DisplayName = "Group2Ability2"),
	Group3Ability1 UMETA(DisplayName = "Group3Ability1"),
	Group3Ability2 UMETA(DisplayName = "Group3Ability2")
};

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSEquipmentAbilityData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = EquipmentAbility)
	TMap<EAbilityType, TSubclassOf<UTPSEquipmentAbilityBase>> EquipmentAbilities;
};
