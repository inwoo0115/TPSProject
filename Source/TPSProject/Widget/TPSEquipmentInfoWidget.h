// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSEquipmentInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSEquipmentInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UWidget* Ability1_1;

	UPROPERTY(meta = (BindWidget))
	class UWidget* Ability1_2;

	UPROPERTY(meta = (BindWidget))
	class UWidget* Ability2_1;

	UPROPERTY(meta = (BindWidget))
	class UWidget* Ability2_2;

	UPROPERTY(meta = (BindWidget))
	class UWidget* Ability3_1;

	UPROPERTY(meta = (BindWidget))
	class UWidget* Ability3_2;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EquipmentName;

	UPROPERTY(meta = (BindWidget))
	class UImage* EquipmentIcon;

	void InitializeWeaponInfo();

	void InitializeDroneInfo();

	void InitializeUltimateInfo();

	void InitializeSpAttackInfo();

protected:
	virtual void NativeConstruct() override;
};
