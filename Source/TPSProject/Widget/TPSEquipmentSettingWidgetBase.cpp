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
	EAbilityType Ability1 = EAbilityType::None;
	EAbilityType Ability2 = EAbilityType::None;
	EAbilityType Ability3 = EAbilityType::None;

	// 장착
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
	// 이미지 장비 텍스쳐 할당
	Icon.LoadSynchronous();
	UTexture2D* IconTexture = Icon.Get();
	if (IconTexture)
		EquipmentIcon->SetBrushFromTexture(IconTexture);

	//// 장비 이름 할당
	EquipmentName->SetText(ContextName);


	// 버튼 & 텍스트 배열 구성
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

		//인스턴스 생성
		UTPSEquipmentAbilityBase* AbilityCDO = Pair.Value->GetDefaultObject<UTPSEquipmentAbilityBase>();

		if (AbilityCDO && Buttons.IsValidIndex(Index) && TextBlocks.IsValidIndex(Index))
		{
			// 1. 텍스트 블록에 이름 바인딩
			TextBlocks[Index]->SetText(AbilityCDO->AbilityName);
			// 2. 버튼에 툴팁 텍스트 바인딩
			UTextBlock* TooltipTextBlock = NewObject<UTextBlock>(this);
			if (TooltipTextBlock)
			{
				TooltipTextBlock->SetText(AbilityCDO->AbilityDescription);
				Buttons[Index]->SetToolTip(TooltipTextBlock);
			}
			// 3. 버튼에 Enum 바인딩
			ButtonToAbilityMap.Add(Buttons[Index], Pair.Key);
		}

		// 현재 선택된 특성 표시
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
