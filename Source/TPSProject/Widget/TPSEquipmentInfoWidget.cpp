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
#include "TPSInventoryWidget.h"

void UTPSEquipmentInfoWidget::InitializeWeaponInfo(UTPSInventoryWidget* Inventory)
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());

	FWeaponContext Context = Pawn->WeaponComponent->GetWeapon()->GetWeaponContext();

	SetImageAndText(Context.WeaponIcon, Context.WeaponName);
	UTPSGameInstance* GI = Cast<UTPSGameInstance>(GetGameInstance());
	SetAbilities(GI->WeaponAbilityList, Inventory);
	SetSlotType(EAbilityType::WeaponAbility);
}

void UTPSEquipmentInfoWidget::InitializeDroneInfo(UTPSInventoryWidget* Inventory)
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());

	const ATPSDroneSkillBase* Equipment = Cast<ATPSDroneSkillBase>(Pawn->DroneComponent->GetEquipment());

	SetImageAndText(Equipment->GetSkillContext().SkillEquipmentIcon, Equipment->GetSkillContext().SkillEquipmentName);
	UTPSGameInstance* GI = Cast<UTPSGameInstance>(GetGameInstance());
	SetAbilities(GI->DroneAbilityList, Inventory);
	SetSlotType(EAbilityType::DroneAbility);
}

void UTPSEquipmentInfoWidget::InitializeUltimateInfo(UTPSInventoryWidget* Inventory)
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());

	const ATPSUltimateSkillBase* Equipment = Cast<ATPSUltimateSkillBase>(Pawn->UltimateComponent->GetEquipment());

	SetImageAndText(Equipment->GetSkillContext().SkillEquipmentIcon, Equipment->GetSkillContext().SkillEquipmentName);
	UTPSGameInstance* GI = Cast<UTPSGameInstance>(GetGameInstance());
	SetAbilities(GI->UltimateAbilityList, Inventory);
	SetSlotType(EAbilityType::UltimateAbility);
}

void UTPSEquipmentInfoWidget::InitializeSpAttackInfo(UTPSInventoryWidget* Inventory)
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());

	const ATPSSpAttackSkillBase* Equipment = Cast<ATPSSpAttackSkillBase>(Pawn->SpAttackComponent->GetEquipment());

	SetImageAndText(Equipment->GetSkillContext().SkillEquipmentIcon, Equipment->GetSkillContext().SkillEquipmentName);
	UTPSGameInstance* GI = Cast<UTPSGameInstance>(GetGameInstance());
	SetAbilities(GI->SpAttackAbilityList, Inventory);
	SetSlotType(EAbilityType::SpAttackAbility);
}

void UTPSEquipmentInfoWidget::UpdateWeaponInfoData()
{
	UTPSGameInstance* GI = Cast<UTPSGameInstance>(GetGameInstance());
	if (!GI) return;

	AddSlotItemToData(GI->WeaponAbilityList, Slot1_1, EAbilityType::Group1Ability1);
	AddSlotItemToData(GI->WeaponAbilityList, Slot1_2, EAbilityType::Group1Ability2);
	AddSlotItemToData(GI->WeaponAbilityList, Slot2_1, EAbilityType::Group2Ability1);
	AddSlotItemToData(GI->WeaponAbilityList, Slot2_2, EAbilityType::Group2Ability2);
	AddSlotItemToData(GI->WeaponAbilityList, Slot3_1, EAbilityType::Group3Ability1);
	AddSlotItemToData(GI->WeaponAbilityList, Slot3_2, EAbilityType::Group3Ability2);

	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
	if (!Pawn) return;

	Pawn->WeaponComponent->EquippedWeapon->AbilityList.Add(EAbilityType::Group1Ability1, nullptr);
	Pawn->WeaponComponent->EquippedWeapon->AbilityList.Add(EAbilityType::Group1Ability2, nullptr);
	Pawn->WeaponComponent->EquippedWeapon->AbilityList.Add(EAbilityType::Group2Ability1, nullptr);
	Pawn->WeaponComponent->EquippedWeapon->AbilityList.Add(EAbilityType::Group2Ability2, nullptr);
	Pawn->WeaponComponent->EquippedWeapon->AbilityList.Add(EAbilityType::Group3Ability1, nullptr);
	Pawn->WeaponComponent->EquippedWeapon->AbilityList.Add(EAbilityType::Group3Ability2, nullptr);

	for (const TPair<EAbilityType, TObjectPtr<UTPSAbilityItem>>& Pair : GI->WeaponAbilityList)
	{
		EAbilityType AbilityType = Pair.Key;
		UTPSAbilityItem* Item = Pair.Value;

		if (Item && Item->AbilityClass)
		{
			Pawn->WeaponComponent->EquippedWeapon->AbilityList.Add(AbilityType, Item->AbilityClass);
		}
	}

	// 장착된 특성 초기화
	Pawn->WeaponComponent->EquipWeapon(
		GI->WeaponClass,
		EAbilityType::None,
		EAbilityType::None,
		EAbilityType::None
	);
}

void UTPSEquipmentInfoWidget::UpdateDroneInfoData()
{
	UTPSGameInstance* GI = Cast<UTPSGameInstance>(GetGameInstance());
	if (!GI) return;

	AddSlotItemToData(GI->DroneAbilityList, Slot1_1, EAbilityType::Group1Ability1);
	AddSlotItemToData(GI->DroneAbilityList, Slot1_2, EAbilityType::Group1Ability2);
	AddSlotItemToData(GI->DroneAbilityList, Slot2_1, EAbilityType::Group2Ability1);
	AddSlotItemToData(GI->DroneAbilityList, Slot2_2, EAbilityType::Group2Ability2);
	AddSlotItemToData(GI->DroneAbilityList, Slot3_1, EAbilityType::Group3Ability1);
	AddSlotItemToData(GI->DroneAbilityList, Slot3_2, EAbilityType::Group3Ability2);

	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
	if (!Pawn) return;

	Pawn->DroneComponent->Equipment->AbilityList.Empty();

	Pawn->DroneComponent->Equipment->AbilityList.Add(EAbilityType::Group1Ability1, nullptr);
	Pawn->DroneComponent->Equipment->AbilityList.Add(EAbilityType::Group1Ability2, nullptr);
	Pawn->DroneComponent->Equipment->AbilityList.Add(EAbilityType::Group2Ability1, nullptr);
	Pawn->DroneComponent->Equipment->AbilityList.Add(EAbilityType::Group2Ability2, nullptr);
	Pawn->DroneComponent->Equipment->AbilityList.Add(EAbilityType::Group3Ability1, nullptr);
	Pawn->DroneComponent->Equipment->AbilityList.Add(EAbilityType::Group3Ability2, nullptr);

	for (const TPair<EAbilityType, TObjectPtr<UTPSAbilityItem>>& Pair : GI->DroneAbilityList)
	{
		EAbilityType AbilityType = Pair.Key;
		UTPSAbilityItem* Item = Pair.Value;

		if (Item && Item->AbilityClass)
		{
			Pawn->DroneComponent->Equipment->AbilityList.Add(AbilityType, Item->AbilityClass);
		}
	}

	// 장착된 특성 초기화
	Pawn->DroneComponent->Equip(
		GI->DroneSkillEquipmentClass,
		EAbilityType::None,
		EAbilityType::None,
		EAbilityType::None
	);
}

void UTPSEquipmentInfoWidget::UpdateUltimateInfoData()
{
	UTPSGameInstance* GI = Cast<UTPSGameInstance>(GetGameInstance());
	if (!GI) return;

	AddSlotItemToData(GI->UltimateAbilityList, Slot1_1, EAbilityType::Group1Ability1);
	AddSlotItemToData(GI->UltimateAbilityList, Slot1_2, EAbilityType::Group1Ability2);
	AddSlotItemToData(GI->UltimateAbilityList, Slot2_1, EAbilityType::Group2Ability1);
	AddSlotItemToData(GI->UltimateAbilityList, Slot2_2, EAbilityType::Group2Ability2);
	AddSlotItemToData(GI->UltimateAbilityList, Slot3_1, EAbilityType::Group3Ability1);
	AddSlotItemToData(GI->UltimateAbilityList, Slot3_2, EAbilityType::Group3Ability2);

	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
	if (!Pawn) return;

	Pawn->UltimateComponent->Equipment->AbilityList.Empty();
	Pawn->UltimateComponent->Equipment->AbilityList.Add(EAbilityType::Group1Ability1, nullptr);
	Pawn->UltimateComponent->Equipment->AbilityList.Add(EAbilityType::Group1Ability2, nullptr);
	Pawn->UltimateComponent->Equipment->AbilityList.Add(EAbilityType::Group2Ability1, nullptr);
	Pawn->UltimateComponent->Equipment->AbilityList.Add(EAbilityType::Group2Ability2, nullptr);
	Pawn->UltimateComponent->Equipment->AbilityList.Add(EAbilityType::Group3Ability1, nullptr);
	Pawn->UltimateComponent->Equipment->AbilityList.Add(EAbilityType::Group3Ability2, nullptr);

	for (const TPair<EAbilityType, TObjectPtr<UTPSAbilityItem>>& Pair : GI->UltimateAbilityList)
	{
		EAbilityType AbilityType = Pair.Key;
		UTPSAbilityItem* Item = Pair.Value;

		if (Item && Item->AbilityClass)
		{
			Pawn->UltimateComponent->Equipment->AbilityList.Add(AbilityType, Item->AbilityClass);
		}
	}

	// 장착된 특성 초기화
	Pawn->UltimateComponent->Equip(
		GI->UltimateSkillEquipmentClass,
		EAbilityType::None,
		EAbilityType::None,
		EAbilityType::None
	);
}

void UTPSEquipmentInfoWidget::UpdateSpAttackInfoData()
{
	UTPSGameInstance* GI = Cast<UTPSGameInstance>(GetGameInstance());
	if (!GI) return;

	AddSlotItemToData(GI->SpAttackAbilityList, Slot1_1, EAbilityType::Group1Ability1);
	AddSlotItemToData(GI->SpAttackAbilityList, Slot1_2, EAbilityType::Group1Ability2);
	AddSlotItemToData(GI->SpAttackAbilityList, Slot2_1, EAbilityType::Group2Ability1);
	AddSlotItemToData(GI->SpAttackAbilityList, Slot2_2, EAbilityType::Group2Ability2);
	AddSlotItemToData(GI->SpAttackAbilityList, Slot3_1, EAbilityType::Group3Ability1);
	AddSlotItemToData(GI->SpAttackAbilityList, Slot3_2, EAbilityType::Group3Ability2);

	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
	if (!Pawn) return;

	Pawn->SpAttackComponent->Equipment->AbilityList.Empty();
	Pawn->SpAttackComponent->Equipment->AbilityList.Add(EAbilityType::Group1Ability1, nullptr);
	Pawn->SpAttackComponent->Equipment->AbilityList.Add(EAbilityType::Group1Ability2, nullptr);
	Pawn->SpAttackComponent->Equipment->AbilityList.Add(EAbilityType::Group2Ability1, nullptr);
	Pawn->SpAttackComponent->Equipment->AbilityList.Add(EAbilityType::Group2Ability2, nullptr);
	Pawn->SpAttackComponent->Equipment->AbilityList.Add(EAbilityType::Group3Ability1, nullptr);
	Pawn->SpAttackComponent->Equipment->AbilityList.Add(EAbilityType::Group3Ability2, nullptr);

	for (const TPair<EAbilityType, TObjectPtr<UTPSAbilityItem>>& Pair : GI->SpAttackAbilityList)
	{
		EAbilityType AbilityType = Pair.Key;
		UTPSAbilityItem* Item = Pair.Value;

		if (Item && Item->AbilityClass)
		{
			Pawn->SpAttackComponent->Equipment->AbilityList.Add(AbilityType, Item->AbilityClass);
		}
	}

	// 장착된 특성 초기화
	Pawn->SpAttackComponent->Equip(
		GI->SpAttackSkillEquipmentClass,
		EAbilityType::None,
		EAbilityType::None,
		EAbilityType::None
	);
}

void UTPSEquipmentInfoWidget::AddSlotItemToData(TMap<EAbilityType, TObjectPtr<class UTPSAbilityItem>>& List, UTPSEquipmentInfoSlotWidget* InfoSlot, EAbilityType Type)
{
	if (InfoSlot->Ability && InfoSlot->Ability->AbilityItem)
	{
		UTPSAbilityItem* NewCopy = DuplicateObject<UTPSAbilityItem>(InfoSlot->Ability->AbilityItem, this);
		List.Add(Type, NewCopy);
	}
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

void UTPSEquipmentInfoWidget::SetAbilities(TMap<EAbilityType, TObjectPtr<class UTPSAbilityItem>> List, UTPSInventoryWidget* Inventory)
{
	if (List.Contains(EAbilityType::Group1Ability1))
	{
		UTPSAbilityItem* Item = List[EAbilityType::Group1Ability1];

		Slot1_1->UpdateSlot(Item, Inventory);
	}

	if (List.Contains(EAbilityType::Group1Ability2))
	{
		UTPSAbilityItem* Item = List[EAbilityType::Group1Ability2];

		Slot1_2->UpdateSlot(Item, Inventory);
	}

	if (List.Contains(EAbilityType::Group2Ability1))
	{
		UTPSAbilityItem* Item = List[EAbilityType::Group2Ability1];

		Slot2_1->UpdateSlot(Item, Inventory);
	}

	if (List.Contains(EAbilityType::Group2Ability2))
	{
		UTPSAbilityItem* Item = List[EAbilityType::Group2Ability2];

		Slot2_2->UpdateSlot(Item, Inventory);
	}

	if (List.Contains(EAbilityType::Group3Ability1))
	{
		UTPSAbilityItem* Item = List[EAbilityType::Group3Ability1];

		Slot3_1->UpdateSlot(Item, Inventory);
	}

	if (List.Contains(EAbilityType::Group3Ability2))
	{
		UTPSAbilityItem* Item = List[EAbilityType::Group3Ability2];

		Slot3_2->UpdateSlot(Item, Inventory);
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
