// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityData.h"
#include "TPSAbilitySelectWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSAbilitySelectWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	// ��� �� ��ư ���
	TMap<int32, UButton*> RowSelectedButtons;

	// ��ư Enum ����
	TMap<UButton*, EAbilityType> ButtonToAbilityMap;

	// ��ư ��� �Լ�
	void ToggleRowSelection(UButton* Button, int32 RowIndex);

	// ��ư ���� �ʱ�ȭ
	void ResetToggleButton();

	// ��ư Ŭ�� �̺�Ʈ
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnCloseWindowButtonClicked();

	UFUNCTION()
	void OnEquipment01Clicked();

	UFUNCTION()
	void OnEquipment02Clicked();

	UFUNCTION()
	virtual void OnEquipment01ConfrimClicked();

	UFUNCTION()
	virtual void OnEquipment02ConfrimClicked();

	UFUNCTION()
	void OnEquipment01Ability1_1Clicked();

	UFUNCTION()
	void OnEquipment01Ability1_2Clicked();

	UFUNCTION()
	void OnEquipment01Ability2_1Clicked();

	UFUNCTION()
	void OnEquipment01Ability2_2Clicked();

	UFUNCTION()
	void OnEquipment01Ability3_1Clicked();

	UFUNCTION()
	void OnEquipment01Ability3_2Clicked();

	UFUNCTION()
	void OnEquipment02Ability1_1Clicked();

	UFUNCTION()
	void OnEquipment02Ability1_2Clicked();

	UFUNCTION()
	void OnEquipment02Ability2_1Clicked();

	UFUNCTION()
	void OnEquipment02Ability2_2Clicked();

	UFUNCTION()
	void OnEquipment02Ability3_1Clicked();

	UFUNCTION()
	void OnEquipment02Ability3_2Clicked();

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* CloseWindowButton;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Equipment01;

	UPROPERTY(meta = (BindWidget))
	class UButton* EquipButton01;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Equipment02;

	UPROPERTY(meta = (BindWidget))
	class UButton* EquipButton02;

	// 1�� ��� Ability
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Equipment01Ability;

	UPROPERTY(meta = (BindWidget))
	class UButton* Equipment01Ability1_1;

	UPROPERTY(meta = (BindWidget))
	class UButton* Equipment01Ability1_2;

	UPROPERTY(meta = (BindWidget))
	class UButton* Equipment01Ability2_1;

	UPROPERTY(meta = (BindWidget))
	class UButton* Equipment01Ability2_2;

	UPROPERTY(meta = (BindWidget))
	class UButton* Equipment01Ability3_1;

	UPROPERTY(meta = (BindWidget))
	class UButton* Equipment01Ability3_2;

	UPROPERTY(meta = (BindWidget))
	class UButton* ConfrimButton01;

	// 2�� ��� �����Ƽ
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Equipment02Ability;

	UPROPERTY(meta = (BindWidget))
	class UButton* Equipment02Ability1_1;

	UPROPERTY(meta = (BindWidget))
	class UButton* Equipment02Ability1_2;

	UPROPERTY(meta = (BindWidget))
	class UButton* Equipment02Ability2_1;

	UPROPERTY(meta = (BindWidget))
	class UButton* Equipment02Ability2_2;

	UPROPERTY(meta = (BindWidget))
	class UButton* Equipment02Ability3_1;

	UPROPERTY(meta = (BindWidget))
	class UButton* Equipment02Ability3_2;

	UPROPERTY(meta = (BindWidget))
	class UButton* ConfrimButton02;
};
