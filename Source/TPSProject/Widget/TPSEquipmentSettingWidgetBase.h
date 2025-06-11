// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityData.h"
#include "TPSEquipmentSettingWidgetBase.generated.h"


/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSEquipmentSettingWidgetBase : public UUserWidget
{
	GENERATED_BODY()


protected:
	// ��� �� ��ư ���
	TMap<int32, UButton*> RowSelectedButtons;

	// ��ư Enum ����
	TMap<UButton*, EAbilityType> ButtonToAbilityMap;

	// ��ư ��� �Լ�
	void ToggleRowSelection(UButton* Button, int32 RowIndex);

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnCloseWindowClicked();

	UFUNCTION()
	void OnEquipButtonClicked();

	UFUNCTION()
	void OnAbility1_1Clicked();

	UFUNCTION()
	void OnAbility1_2Clicked();

	UFUNCTION()
	void OnAbility2_1Clicked();

	UFUNCTION()
	void OnAbility2_2Clicked();

	UFUNCTION()
	void OnAbility3_1Clicked();

	UFUNCTION()
	void OnAbility3_2Clicked();

	UFUNCTION()
	virtual void OnConfirmButtonClicked();

	UFUNCTION()
	virtual void InitializeWidget();

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* CloseWindowButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* EquipButton;

	UPROPERTY(meta = (BindWidget))
	class UImage* EquipmentIcon;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EquipmentName;

	UPROPERTY(meta = (BindWidget))
	class UButton* EquipmentAbility1_1;

	UPROPERTY(meta = (BindWidget))
	class UButton* EquipmentAbility1_2;

	UPROPERTY(meta = (BindWidget))
	class UButton* EquipmentAbility2_1;

	UPROPERTY(meta = (BindWidget))
	class UButton* EquipmentAbility2_2;

	UPROPERTY(meta = (BindWidget))
	class UButton* EquipmentAbility3_1;

	UPROPERTY(meta = (BindWidget))
	class UButton* EquipmentAbility3_2;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EquipmentAbilityText1_1;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EquipmentAbilityText1_2;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EquipmentAbilityText2_1;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EquipmentAbilityText2_2;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EquipmentAbilityText3_1;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EquipmentAbilityText3_2;

	UPROPERTY(meta = (BindWidget))
	class UButton* ConfrimButton;
};
