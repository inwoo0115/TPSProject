// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/TPSEquipmentSettingWidgetBase.h"
#include "TPSSpAttackSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSSpAttackSettingWidget : public UTPSEquipmentSettingWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void EquipBySelectWidget(EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3) override;

};
