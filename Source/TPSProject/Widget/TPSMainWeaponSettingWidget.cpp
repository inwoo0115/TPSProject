// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSMainWeaponSettingWidget.h"
#include "CharacterComponent/TPSWeaponComponent.h"
#include "Character/TPSCharacterBase.h"
#include "GameInstance/TPSGameInstance.h"
#include "Components/Image.h"



void UTPSMainWeaponSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ConfrimButton)
		ConfrimButton->OnClicked.AddDynamic(this, &UTPSMainWeaponSettingWidget::OnConfirmButtonClicked);


	// 위젯 초기화
	InitializeWidget();
}

void UTPSMainWeaponSettingWidget::InitializeWidget()
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
	if (Pawn && Pawn->WeaponComponent->GetWeapon())
	{
		const ATPSWeaponBase* Weapon = Pawn->WeaponComponent->GetWeapon();

		// 이미지 장비 텍스쳐 할당
		Weapon->EquipmentIcon.LoadSynchronous();
		UTexture2D* IconTexture = Weapon->EquipmentIcon.Get();
		if (IconTexture)
			EquipmentIcon->SetBrushFromTexture(IconTexture);

		//// 장비 이름 할당
		EquipmentName->SetText(Weapon->EquipmentName);


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
		for (const TPair<EAbilityType, TSubclassOf<UTPSEquipmentAbilityBase>>& Pair : Weapon->AbilityData->EquipmentAbilities)
		{
			if (!Pair.Value) continue;

			// 인스턴스 생성
			UTPSEquipmentAbilityBase* AbilityCDO = Pair.Value->GetDefaultObject<UTPSEquipmentAbilityBase>();
			if (!AbilityCDO) continue;

			if (Buttons.IsValidIndex(Index) && TextBlocks.IsValidIndex(Index))
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
			for (UTPSEquipmentAbilityBase* Ability : Weapon->AbilitySlot)
			{
				// 객체 자체 비교는 좀 그렇긴 함 TODO: 추후에 데이터로 관리
				if (AbilityCDO->GetClass() == Ability->GetClass())
				{
					ToggleRowSelection(Buttons[Index], (Index / 2) + 1);
				}
			}
			++Index;
		}
	}
}

void UTPSMainWeaponSettingWidget::OnConfirmButtonClicked()
{
	// 무기 장착
	EAbilityType Ability1 = EAbilityType::None;
	EAbilityType Ability2 = EAbilityType::None;
	EAbilityType Ability3 = EAbilityType::None;


	// TODO : Weapon임시 장착 (나중에 게임 인스턴스에서 한번에 불러올것)
	auto TPSGameInstance = Cast<UTPSGameInstance>(GetGameInstance());
	if (TPSGameInstance)
	{
		// 무기 장착
		ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
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

		Pawn->WeaponComponent->EquipWeapon(
			TPSGameInstance->WeaponClass,
			Ability1,
			Ability2,
			Ability3
		);
	}
}


