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


	// ���� �ʱ�ȭ
	InitializeWidget();
}

void UTPSMainWeaponSettingWidget::InitializeWidget()
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
	if (Pawn && Pawn->WeaponComponent->GetWeapon())
	{
		const ATPSWeaponBase* Weapon = Pawn->WeaponComponent->GetWeapon();

		// �̹��� ��� �ؽ��� �Ҵ�
		Weapon->EquipmentIcon.LoadSynchronous();
		UTexture2D* IconTexture = Weapon->EquipmentIcon.Get();
		if (IconTexture)
			EquipmentIcon->SetBrushFromTexture(IconTexture);

		//// ��� �̸� �Ҵ�
		EquipmentName->SetText(Weapon->EquipmentName);


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
		for (const TPair<EAbilityType, TSubclassOf<UTPSEquipmentAbilityBase>>& Pair : Weapon->AbilityData->EquipmentAbilities)
		{
			if (!Pair.Value) continue;

			// �ν��Ͻ� ����
			UTPSEquipmentAbilityBase* AbilityCDO = Pair.Value->GetDefaultObject<UTPSEquipmentAbilityBase>();
			if (!AbilityCDO) continue;

			if (Buttons.IsValidIndex(Index) && TextBlocks.IsValidIndex(Index))
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
			for (UTPSEquipmentAbilityBase* Ability : Weapon->AbilitySlot)
			{
				// ��ü ��ü �񱳴� �� �׷��� �� TODO: ���Ŀ� �����ͷ� ����
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
	// ���� ����
	EAbilityType Ability1 = EAbilityType::None;
	EAbilityType Ability2 = EAbilityType::None;
	EAbilityType Ability3 = EAbilityType::None;


	// TODO : Weapon�ӽ� ���� (���߿� ���� �ν��Ͻ����� �ѹ��� �ҷ��ð�)
	auto TPSGameInstance = Cast<UTPSGameInstance>(GetGameInstance());
	if (TPSGameInstance)
	{
		// ���� ����
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


