// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSEquipmentSettingWidgetBase.h"
#include "TPSEquipmentSettingWidgetBase.h"
#include "CharacterEquipment/TPSAbilityEquipmentBase.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "Character/TPSCharacterBase.h"

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
	EAbilityType Ability1 = EAbilityType::None;
	EAbilityType Ability2 = EAbilityType::None;
	EAbilityType Ability3 = EAbilityType::None;

	// ����
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());

	if (Pawn)
	{
		if (RowSelectedButtons.Contains(1))
		{
			Ability1 = ButtonToAbilityMap[RowSelectedButtons[1]];
		}
		if (RowSelectedButtons.Contains(2))
		{
			Ability2 = ButtonToAbilityMap[RowSelectedButtons[2]];
		}
		if (RowSelectedButtons.Contains(3))
		{
			Ability3 = ButtonToAbilityMap[RowSelectedButtons[3]];
		}
		EquipBySelectWidget(Ability1, Ability2, Ability3);
	}
}

void UTPSEquipmentSettingWidgetBase::EquipBySelectWidget(EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
}

void UTPSEquipmentSettingWidgetBase::InitializeWidget(const ATPSAbilityEquipmentBase* CurrentEquipment, TSoftObjectPtr<UTexture2D> Icon, FText ContextName)
{
	// �̹��� ��� �ؽ��� �Ҵ�
	Icon.LoadSynchronous();
	UTexture2D* IconTexture = Icon.Get();
	if (IconTexture)
		EquipmentIcon->SetBrushFromTexture(IconTexture);

	//// ��� �̸� �Ҵ�
	EquipmentName->SetText(ContextName);


	// ��ư & �ؽ�Ʈ �迭 ����
	TArray<UButton*> Buttons = {
		EquipmentAbility1_1, EquipmentAbility1_2,
		EquipmentAbility2_1, EquipmentAbility2_2,
		EquipmentAbility3_1, EquipmentAbility3_2
	};

	TArray<UTextBlock*> TextBlocks = {
		EquipmentAbilityText1_1, EquipmentAbilityText1_2,
		EquipmentAbilityText2_1, EquipmentAbilityText2_2,
		EquipmentAbilityText3_1, EquipmentAbilityText3_2
	};

	int32 Index = 0;
	for (const TPair<EAbilityType, TSubclassOf<UTPSEquipmentAbilityBase>>& Pair : CurrentEquipment->AbilityList)
	{
		if (!Pair.Value)
		{
			ButtonToAbilityMap.Add(Buttons[Index], EAbilityType::None);
			++Index;
			continue;
		}

		//�ν��Ͻ� ����
		UTPSEquipmentAbilityBase* AbilityCDO = Pair.Value->GetDefaultObject<UTPSEquipmentAbilityBase>();

		if (AbilityCDO && Buttons.IsValidIndex(Index) && TextBlocks.IsValidIndex(Index))
		{
			// 1. �ؽ�Ʈ ��Ͽ� �̸� ���ε�
			TextBlocks[Index]->SetText(AbilityCDO->AbilityName);
			// 2. ��ư�� ���� �ؽ�Ʈ ���ε�
			UTextBlock* TooltipTextBlock = NewObject<UTextBlock>(this);
			if (TooltipTextBlock)
			{
				TooltipTextBlock->SetText(AbilityCDO->AbilityDescription);
				Buttons[Index]->SetToolTip(TooltipTextBlock);
			}
			// 3. ��ư�� Enum ���ε�
			ButtonToAbilityMap.Add(Buttons[Index], Pair.Key);
		}

		// ���� ���õ� Ư�� ǥ��
		for (UTPSEquipmentAbilityBase* Ability : CurrentEquipment->AbilitySlot)
		{
			if (AbilityCDO->GetClass() == Ability->GetClass())
			{
				ToggleRowSelection(Buttons[Index], (Index / 2) + 1);
			}
		}
		++Index;
	}

}
