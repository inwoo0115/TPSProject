// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterEquipmentAbility/TPSAbilityType.h"
#include "TPSAbilityItem.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSAbilityItem : public UObject
{
	GENERATED_BODY()

public:
	UTPSAbilityItem();

	void InitItem(const FName& InName, TSubclassOf<class UTPSEquipmentAbilityBase> InClass);

	FText GetAbilityNameText() const;

	FText GetAbilityDescriptionText() const;

	EAbilityType GetAbilityType() const;

	class UTexture2D* GetItemImage();

protected:
	UPROPERTY()
	FName AbilityName;

	UPROPERTY()
	TSubclassOf<class UTPSEquipmentAbilityBase> AbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UTexture2D> ItemImage;

	bool bIsActive = true;
};
