// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/TPSAbilitySelectWidgetBase.h"
#include "TPSWeaponAbilitySelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSWeaponAbilitySelectWidget : public UTPSAbilitySelectWidgetBase
{
	GENERATED_BODY()
	
protected:
	// 버튼 클릭 이벤트
	virtual void NativeConstruct() override;

	virtual void OnEquipment01ConfrimClicked() override;

	virtual void OnEquipment02ConfrimClicked() override;

};
