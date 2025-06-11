// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSEquipmentSettingWidgetBase.h"
#include "TPSEquipmentSettingWidgetBase.h"
#include "Components/Button.h"

void UTPSEquipmentSettingWidgetBase::ToggleRowSelection(UButton* Button, int32 RowIndex)
{
	if (!Button) return;

	// ���� ���õ� ��ư�� �ִٸ� ���� �ʱ�ȭ
	if (RowSelectedButtons.Contains(RowIndex))
	{
		UButton* PrevButton = RowSelectedButtons[RowIndex];
		if (PrevButton && PrevButton != Button)
		{
			PrevButton->SetBackgroundColor(FLinearColor::White);
		}
	}

	// ���� ��ư �ٽ� ������ ���� ����
	if (RowSelectedButtons.Contains(RowIndex) && RowSelectedButtons[RowIndex] == Button)
	{
		Button->SetBackgroundColor(FLinearColor::White);
		RowSelectedButtons.Remove(RowIndex);
	}
	else
	{
		// ���ο� ��ư ����
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
	RemoveFromParent();  // ���� ������ ȭ�鿡�� ����
}

void UTPSEquipmentSettingWidgetBase::OnEquipButtonClicked()
{
	// ��� ���� ���� ����
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
	// Ư�� ���� ����
}

void UTPSEquipmentSettingWidgetBase::InitializeWidget()
{
	// ���� ���� ĳ���Ϳ��� ��������
}
