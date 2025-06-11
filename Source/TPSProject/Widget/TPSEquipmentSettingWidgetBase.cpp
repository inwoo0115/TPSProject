// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSEquipmentSettingWidgetBase.h"
#include "TPSEquipmentSettingWidgetBase.h"
#include "Components/Button.h"

void UTPSEquipmentSettingWidgetBase::ToggleRowSelection(UButton* Button, int32 RowIndex)
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

void UTPSEquipmentSettingWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseWindowButton)
		CloseWindowButton->OnClicked.AddDynamic(this, &UTPSEquipmentSettingWidgetBase::OnCloseWindowClicked);

	if (EquipButton)
		EquipButton->OnClicked.AddDynamic(this, &UTPSEquipmentSettingWidgetBase::OnEquipButtonClicked);

	if (EquipmentAbility1_1)
		EquipmentAbility1_1->OnClicked.AddDynamic(this, &UTPSEquipmentSettingWidgetBase::OnAbility1_1Clicked);

	if (EquipmentAbility1_2)
		EquipmentAbility1_2->OnClicked.AddDynamic(this, &UTPSEquipmentSettingWidgetBase::OnAbility1_2Clicked);

	if (EquipmentAbility2_1)
		EquipmentAbility2_1->OnClicked.AddDynamic(this, &UTPSEquipmentSettingWidgetBase::OnAbility2_1Clicked);

	if (EquipmentAbility2_2)
		EquipmentAbility2_2->OnClicked.AddDynamic(this, &UTPSEquipmentSettingWidgetBase::OnAbility2_2Clicked);

	if (EquipmentAbility3_1)
		EquipmentAbility3_1->OnClicked.AddDynamic(this, &UTPSEquipmentSettingWidgetBase::OnAbility3_1Clicked);

	if (EquipmentAbility3_2)
		EquipmentAbility3_2->OnClicked.AddDynamic(this, &UTPSEquipmentSettingWidgetBase::OnAbility3_2Clicked);
}

void UTPSEquipmentSettingWidgetBase::OnCloseWindowClicked()
{
	RemoveFromParent();  // 현재 위젯을 화면에서 제거
}

void UTPSEquipmentSettingWidgetBase::OnEquipButtonClicked()
{
	// 장비 장착 위젯 띄우기
}

void UTPSEquipmentSettingWidgetBase::OnAbility1_1Clicked()
{
	ToggleRowSelection(EquipmentAbility1_1, 1);
}

void UTPSEquipmentSettingWidgetBase::OnAbility1_2Clicked()
{
	ToggleRowSelection(EquipmentAbility1_2, 1);

}

void UTPSEquipmentSettingWidgetBase::OnAbility2_1Clicked()
{
	ToggleRowSelection(EquipmentAbility2_1, 2);

}

void UTPSEquipmentSettingWidgetBase::OnAbility2_2Clicked()
{
	ToggleRowSelection(EquipmentAbility2_2, 2);

}

void UTPSEquipmentSettingWidgetBase::OnAbility3_1Clicked()
{
	ToggleRowSelection(EquipmentAbility3_1, 3);

}

void UTPSEquipmentSettingWidgetBase::OnAbility3_2Clicked()
{
	ToggleRowSelection(EquipmentAbility3_2, 3);

}

void UTPSEquipmentSettingWidgetBase::OnConfirmButtonClicked()
{
	// 특성 선택 적용
}

void UTPSEquipmentSettingWidgetBase::InitializeWidget()
{
	// 위젯 정보 캐릭터에서 가져오기
}
