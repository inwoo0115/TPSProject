// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSAbilitySelectWidgetBase.h"
#include "Components/CanvasPanel.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityData.h"
#include "GameInstance/TPSUiSubsystem.h"
#include "Components/Button.h"

void UTPSAbilitySelectWidgetBase::ToggleRowSelection(UButton* Button, int32 RowIndex)
{
    if (!Button) return;

    // 기존 선택된 버튼이 있다면 색상 초기화
    if (RowSelectedButtons.Contains(RowIndex))
    {
        UButton* PrevButton = RowSelectedButtons[RowIndex];
        if (PrevButton && PrevButton != Button)
        {
            PrevButton->SetBackgroundColor(FLinearColor::White);
        }
    }

    // 같은 버튼 다시 누르면 선택 해제
    if (RowSelectedButtons.Contains(RowIndex) && RowSelectedButtons[RowIndex] == Button)
    {
        Button->SetBackgroundColor(FLinearColor::White);
        RowSelectedButtons.Remove(RowIndex);
    }
    else
    {
        // 새로운 버튼 선택
        Button->SetBackgroundColor(FLinearColor::Blue);
        RowSelectedButtons.Add(RowIndex, Button);
    }
}

void UTPSAbilitySelectWidgetBase::ResetToggleButton()
{
    for (TPair<int32, UButton*>& Pair : RowSelectedButtons)
    {
        if (Pair.Value)
        {
            Pair.Value->SetBackgroundColor(FLinearColor::White);
            RowSelectedButtons.Remove(Pair.Key);
        }
    }

    RowSelectedButtons.Empty();
}

void UTPSAbilitySelectWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

    // 버튼 바인딩
    if (CloseWindowButton) CloseWindowButton->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnCloseWindowButtonClicked);

    if (EquipButton01) EquipButton01->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnEquipment01Clicked);
    if (EquipButton02) EquipButton02->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnEquipment02Clicked);
    if (ConfrimButton01) ConfrimButton01->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnEquipment01ConfrimClicked);
    if (ConfrimButton02) ConfrimButton02->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnEquipment02ConfrimClicked);

    if (Equipment01Ability1_1) Equipment01Ability1_1->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnEquipment01Ability1_1Clicked);
    if (Equipment01Ability1_2) Equipment01Ability1_2->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnEquipment01Ability1_2Clicked);
    if (Equipment01Ability2_1) Equipment01Ability2_1->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnEquipment01Ability2_1Clicked);
    if (Equipment01Ability2_2) Equipment01Ability2_2->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnEquipment01Ability2_2Clicked);
    if (Equipment01Ability3_1) Equipment01Ability3_1->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnEquipment01Ability3_1Clicked);
    if (Equipment01Ability3_2) Equipment01Ability3_2->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnEquipment01Ability3_2Clicked);

    if (Equipment02Ability1_1) Equipment02Ability1_1->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnEquipment02Ability1_1Clicked);
    if (Equipment02Ability1_2) Equipment02Ability1_2->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnEquipment02Ability1_2Clicked);
    if (Equipment02Ability2_1) Equipment02Ability2_1->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnEquipment02Ability2_1Clicked);
    if (Equipment02Ability2_2) Equipment02Ability2_2->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnEquipment02Ability2_2Clicked);
    if (Equipment02Ability3_1) Equipment02Ability3_1->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnEquipment02Ability3_1Clicked);
    if (Equipment02Ability3_2) Equipment02Ability3_2->OnClicked.AddDynamic(this, &UTPSAbilitySelectWidgetBase::OnEquipment02Ability3_2Clicked);

    // 버튼 Enum 매핑
    ButtonToAbilityMap.Add(Equipment01Ability1_1, EAbilityType::Group1Ability1);
    ButtonToAbilityMap.Add(Equipment01Ability1_2, EAbilityType::Group1Ability2);
    ButtonToAbilityMap.Add(Equipment01Ability2_1, EAbilityType::Group2Ability1);
    ButtonToAbilityMap.Add(Equipment01Ability2_2, EAbilityType::Group2Ability2);
    ButtonToAbilityMap.Add(Equipment01Ability3_1, EAbilityType::Group3Ability1);
    ButtonToAbilityMap.Add(Equipment01Ability3_2, EAbilityType::Group3Ability2);

    ButtonToAbilityMap.Add(Equipment02Ability1_1, EAbilityType::Group1Ability1);
    ButtonToAbilityMap.Add(Equipment02Ability1_2, EAbilityType::Group1Ability2);
    ButtonToAbilityMap.Add(Equipment02Ability2_1, EAbilityType::Group2Ability1);
    ButtonToAbilityMap.Add(Equipment02Ability2_2, EAbilityType::Group2Ability2);
    ButtonToAbilityMap.Add(Equipment02Ability3_1, EAbilityType::Group3Ability1);
    ButtonToAbilityMap.Add(Equipment02Ability3_2, EAbilityType::Group3Ability2);

	Equipment01Ability->SetVisibility(ESlateVisibility::Hidden);
    Equipment02Ability->SetVisibility(ESlateVisibility::Hidden);
}

void UTPSAbilitySelectWidgetBase::OnCloseWindowButtonClicked()
{
    ResetToggleButton();
    auto UIsubsystem = GetGameInstance()->GetSubsystem<UTPSUiSubsystem>();
    if (UIsubsystem)
    {
        UIsubsystem->HideCurrentUI();
    }
}

void UTPSAbilitySelectWidgetBase::OnEquipment01Clicked()
{
    Equipment01Ability->SetVisibility(ESlateVisibility::Visible);
    Equipment02Ability->SetVisibility(ESlateVisibility::Hidden);
    ResetToggleButton();
}

void UTPSAbilitySelectWidgetBase::OnEquipment02Clicked()
{
    Equipment01Ability->SetVisibility(ESlateVisibility::Hidden);
    Equipment02Ability->SetVisibility(ESlateVisibility::Visible);
    ResetToggleButton();
}

void UTPSAbilitySelectWidgetBase::OnEquipment01ConfrimClicked()
{
    // 무기 장착
}

void UTPSAbilitySelectWidgetBase::OnEquipment02ConfrimClicked()
{
    // 무기 장착
}

void UTPSAbilitySelectWidgetBase::OnEquipment01Ability1_1Clicked()
{
    ToggleRowSelection(Equipment01Ability1_1, 1);
}

void UTPSAbilitySelectWidgetBase::OnEquipment01Ability1_2Clicked()
{
    ToggleRowSelection(Equipment01Ability1_2, 1);
}

void UTPSAbilitySelectWidgetBase::OnEquipment01Ability2_1Clicked()
{
    ToggleRowSelection(Equipment01Ability2_1, 2);
}

void UTPSAbilitySelectWidgetBase::OnEquipment01Ability2_2Clicked()
{
    ToggleRowSelection(Equipment01Ability2_2, 2);
}

void UTPSAbilitySelectWidgetBase::OnEquipment01Ability3_1Clicked()
{
    ToggleRowSelection(Equipment01Ability3_1, 3);
}

void UTPSAbilitySelectWidgetBase::OnEquipment01Ability3_2Clicked()
{
    ToggleRowSelection(Equipment01Ability3_2, 3);
}

void UTPSAbilitySelectWidgetBase::OnEquipment02Ability1_1Clicked()
{
    ToggleRowSelection(Equipment02Ability1_1, 1);
}

void UTPSAbilitySelectWidgetBase::OnEquipment02Ability1_2Clicked()
{
    ToggleRowSelection(Equipment02Ability1_2, 1);
}

void UTPSAbilitySelectWidgetBase::OnEquipment02Ability2_1Clicked()
{
    ToggleRowSelection(Equipment02Ability2_1, 2);
}

void UTPSAbilitySelectWidgetBase::OnEquipment02Ability2_2Clicked()
{
    ToggleRowSelection(Equipment02Ability2_2, 2);
}

void UTPSAbilitySelectWidgetBase::OnEquipment02Ability3_1Clicked()
{
    ToggleRowSelection(Equipment02Ability3_1, 3);
}

void UTPSAbilitySelectWidgetBase::OnEquipment02Ability3_2Clicked()
{
    ToggleRowSelection(Equipment02Ability3_2, 3);
}
