// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TPSAbilityItem.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSAbilityItem : public UObject
{
	GENERATED_BODY()

public:
	void InitItem(const FName& InName, TSubclassOf<class UTPSEquipmentAbilityBase> InClass);

	FText GetAbilityNameText() const;

	FText GetAbilityDescriptionText() const;
protected:
	FName AbilityName;

	TSubclassOf<class UTPSEquipmentAbilityBase> AbilityClass;

	bool bIsActive = true;
};
