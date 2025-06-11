// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSEquipmentSettingWidgetBase.h"
#include "TPSEquipmentWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnBackArrowButtonClicked();

	UFUNCTION()
	void OnWeapon01Clicked();

	UFUNCTION()
	void OnWeapon02Clicked();

	UFUNCTION()
	void OnSpWeaponClicked();

	UFUNCTION()
	void OnUltimateClicked();

	UFUNCTION()
	void OnDroneClicked();


public:

	UPROPERTY(meta = (BindWidget))
	class UButton* BackArrow;

	UPROPERTY(meta = (BindWidget))
	class UButton* Weapon01;

	UPROPERTY(meta = (BindWidget))
	class UButton* Weapon02;

	UPROPERTY(meta = (BindWidget))
	class UButton* SpWeapon;

	UPROPERTY(meta = (BindWidget))
	class UButton* Ultimate;

	UPROPERTY(meta = (BindWidget))
	class UButton* Drone;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UTPSEquipmentSettingWidgetBase> MainWeaponSettingWidgetClass;

};
