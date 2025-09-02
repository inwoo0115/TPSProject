// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSEquipmentInfoWidget.h"
#include "TPSEquipmentInfoWidget.h"
#include "Character/TPSCharacterBase.h"
#include "CharacterComponent/TPSWeaponComponent.h"
#include "CharacterComponent/TPSDroneSkillComponent.h"
#include "CharacterComponent/TPSSpAttackSkillComponent.h"
#include "CharacterComponent/TPSUltimateComponent.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"
#include "CharacterEquipment/TPSUltimateSkillBase.h"
#include "CharacterEquipment/TPSSpAttackSkillBase.h"
#include "TPSInventoryItemWidget.h"
#include "TPSItemInfoWidget.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "GameInstance/TPSGameInstance.h"
#include "Item/TPSAbilityItem.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "TPSEquipmentInfoSlotWidget.h"

void UTPSEquipmentInfoWidget::InitializeWeaponInfo()
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());

	FWeaponContext Context = Pawn->WeaponComponent->GetWeapon()->GetWeaponContext();

	SetImageAndText(Context.WeaponIcon, Context.WeaponName);
	UTPSGameInstance* GI = Cast<UTPSGameInstance>(GetGameInstance());
	SetAbilities(GI->WeaponAbilityList);
	SetSlotType(EAbilityType::WeaponAbility);
}

void UTPSEquipmentInfoWidget::InitializeDroneInfo()
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());

	const ATPSDroneSkillBase* Equipment = Cast<ATPSDroneSkillBase>(Pawn->DroneComponent->GetEquipment());

	SetImageAndText(Equipment->GetSkillContext().SkillEquipmentIcon, Equipment->GetSkillContext().SkillEquipmentName);
	UTPSGameInstance* GI = Cast<UTPSGameInstance>(GetGameInstance());
	SetAbilities(GI->DroneAbilityList);
	SetSlotType(EAbilityType::DroneAbility);
}

void UTPSEquipmentInfoWidget::InitializeUltimateInfo()
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());

	const ATPSUltimateSkillBase* Equipment = Cast<ATPSUltimateSkillBase>(Pawn->UltimateComponent->GetEquipment());

	SetImageAndText(Equipment->GetSkillContext().SkillEquipmentIcon, Equipment->GetSkillContext().SkillEquipmentName);
	UTPSGameInstance* GI = Cast<UTPSGameInstance>(GetGameInstance());
	SetAbilities(GI->UltimateAbilityList);
	SetSlotType(EAbilityType::UltimateAbility);
}

void UTPSEquipmentInfoWidget::InitializeSpAttackInfo()
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());

	const ATPSSpAttackSkillBase* Equipment = Cast<ATPSSpAttackSkillBase>(Pawn->SpAttackComponent->GetEquipment());

	SetImageAndText(Equipment->GetSkillContext().SkillEquipmentIcon, Equipment->GetSkillContext().SkillEquipmentName);
	UTPSGameInstance* GI = Cast<UTPSGameInstance>(GetGameInstance());
	SetAbilities(GI->SpAttackAbilityList);
	SetSlotType(EAbilityType::SpAttackAbility);
}

void UTPSEquipmentInfoWidget::SetImageAndText(TSoftObjectPtr<UTexture2D> Icon, FText ContextName)
{
	// 이미지 장비 텍스쳐 할당
	Icon.LoadSynchronous();
	UTexture2D* IconTexture = Icon.Get();
	if (IconTexture)
		EquipmentIcon->SetBrushFromTexture(IconTexture);

	// 장비 이름 할당
	EquipmentName->SetText(ContextName);
}

void UTPSEquipmentInfoWidget::SetAbilities(TMap<EAbilityType, TObjectPtr<class UTPSAbilityItem>> List)
{
	if (List.Contains(EAbilityType::Group1Ability1))
	{
		UTPSAbilityItem* Item = List[EAbilityType::Group1Ability1];

		Slot1_1->UpdateSlot(Item);
	}

	if (List.Contains(EAbilityType::Group1Ability2))
	{
		UTPSAbilityItem* Item = List[EAbilityType::Group1Ability2];

		Slot1_2->UpdateSlot(Item);
	}

	if (List.Contains(EAbilityType::Group2Ability1))
	{
		UTPSAbilityItem* Item = List[EAbilityType::Group2Ability1];

		Slot2_1->UpdateSlot(Item);
	}

	if (List.Contains(EAbilityType::Group2Ability2))
	{
		UTPSAbilityItem* Item = List[EAbilityType::Group2Ability2];

		Slot2_2->UpdateSlot(Item);
	}

	if (List.Contains(EAbilityType::Group3Ability1))
	{
		UTPSAbilityItem* Item = List[EAbilityType::Group3Ability1];

		Slot3_1->UpdateSlot(Item);
	}

	if (List.Contains(EAbilityType::Group3Ability2))
	{
		UTPSAbilityItem* Item = List[EAbilityType::Group3Ability2];

		Slot3_2->UpdateSlot(Item);
	}
}

void UTPSEquipmentInfoWidget::SetSlotColor(bool Active)
{
	Slot1_1->SetColor(Active);
	Slot1_2->SetColor(Active);
	Slot2_1->SetColor(Active);
	Slot2_2->SetColor(Active);
	Slot3_1->SetColor(Active);
	Slot3_2->SetColor(Active);
}

void UTPSEquipmentInfoWidget::SetSlotType(EAbilityType AbilityType)
{
	Slot1_1->SlotType = AbilityType;
	Slot1_2->SlotType = AbilityType;
	Slot2_1->SlotType = AbilityType;
	Slot2_2->SlotType = AbilityType;
	Slot3_1->SlotType = AbilityType;
	Slot3_2->SlotType = AbilityType;
}


void UTPSEquipmentInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply UTPSEquipmentInfoWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
	
		return FReply::Handled();
	}
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{

		return FReply::Handled();
	}
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}
