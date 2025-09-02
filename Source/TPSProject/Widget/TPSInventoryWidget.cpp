// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSInventoryWidget.h"
#include "Components/Button.h"
#include "Character/TPSCharacterBase.h"
#include "TPSEquipmentInfoWidget.h"
#include "Gameinstance/TPSUiSubsystem.h"
#include "GameInstance/TPSGameInstance.h"
#include "Components/GridPanel.h"
#include "Item/TPSAbilityItem.h"
#include "TPSInventoryItemWidget.h"
#include "TPSItemInfoWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "CharacterEquipmentAbility/TPSAbilityType.h"
#include "TPSEquipmentInfoSlotWidget.h"

void UTPSInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseWindowButton)
		CloseWindowButton->OnClicked.AddDynamic(this, &UTPSInventoryWidget::OnCloseWindowClicked);

	OnVisibilityChanged.AddDynamic(this, &UTPSInventoryWidget::InitializeWidget);

	if (WeaponInfo)
	{
		if (WeaponInfo->Slot1_1)
			WeaponInfo->Slot1_1->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (WeaponInfo->Slot1_2)
			WeaponInfo->Slot1_2->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (WeaponInfo->Slot2_1)
			WeaponInfo->Slot2_1->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (WeaponInfo->Slot2_2)
			WeaponInfo->Slot2_2->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (WeaponInfo->Slot3_1)
			WeaponInfo->Slot3_1->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (WeaponInfo->Slot3_2)
			WeaponInfo->Slot3_2->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
	}

	if (DroneInfo)
	{
		if (DroneInfo->Slot1_1)
			DroneInfo->Slot1_1->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (DroneInfo->Slot1_2)
			DroneInfo->Slot1_2->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (DroneInfo->Slot2_1)
			DroneInfo->Slot2_1->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (DroneInfo->Slot2_2)
			DroneInfo->Slot2_2->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (DroneInfo->Slot3_1)
			DroneInfo->Slot3_1->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (DroneInfo->Slot3_2)
			DroneInfo->Slot3_2->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
	}

	if (SpAttackInfo)
	{
		if (SpAttackInfo->Slot1_1)
			SpAttackInfo->Slot1_1->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (SpAttackInfo->Slot1_2)
			SpAttackInfo->Slot1_2->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (SpAttackInfo->Slot2_1)
			SpAttackInfo->Slot2_1->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (SpAttackInfo->Slot2_2)
			SpAttackInfo->Slot2_2->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (SpAttackInfo->Slot3_1)
			SpAttackInfo->Slot3_1->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (SpAttackInfo->Slot3_2)
			SpAttackInfo->Slot3_2->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
	}

	if (UltimateInfo)
	{
		if (UltimateInfo->Slot1_1)
			UltimateInfo->Slot1_1->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (UltimateInfo->Slot1_2)
			UltimateInfo->Slot1_2->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (UltimateInfo->Slot2_1)
			UltimateInfo->Slot2_1->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (UltimateInfo->Slot2_2)
			UltimateInfo->Slot2_2->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (UltimateInfo->Slot3_1)
			UltimateInfo->Slot3_1->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
		if (UltimateInfo->Slot3_2)
			UltimateInfo->Slot3_2->OnSlotClicked.AddDynamic(this, &UTPSInventoryWidget::HandleSlotClicked);
	}
}

void UTPSInventoryWidget::HandleItemClicked(UTPSInventoryItemWidget* Item)
{
	EAbilityType Type = Item->AbilityItem->GetAbilityType();

	if (Type == EAbilityType::WeaponAbility)
	{
		WeaponInfo->SetSlotColor(true);
		DroneInfo->SetSlotColor(false);
		SpAttackInfo->SetSlotColor(false);
		UltimateInfo->SetSlotColor(false);
	}
	else if (Type == EAbilityType::DroneAbility)
	{
		DroneInfo->SetSlotColor(true);
		WeaponInfo->SetSlotColor(false);
		SpAttackInfo->SetSlotColor(false);
		UltimateInfo->SetSlotColor(false);
	}
	else if (Type == EAbilityType::SpAttackAbility)
	{
		SpAttackInfo->SetSlotColor(true);
		WeaponInfo->SetSlotColor(false);
		DroneInfo->SetSlotColor(false);
		UltimateInfo->SetSlotColor(false);
	}
	else if (Type == EAbilityType::UltimateAbility)
	{
		UltimateInfo->SetSlotColor(true);
		WeaponInfo->SetSlotColor(false);
		DroneInfo->SetSlotColor(false);
		SpAttackInfo->SetSlotColor(false);
	}

	PendingItem = Item;
}

void UTPSInventoryWidget::HandleSlotClicked(UTPSEquipmentInfoSlotWidget* SlotWidget)
{
	if (PendingItem && !SlotWidget->Ability && SlotWidget->SlotType == PendingItem->AbilityItem->GetAbilityType())
	{
		SlotWidget->UpdateSlot(PendingItem->AbilityItem);
		PendingItem->RemoveFromParent();
		PendingItem = nullptr;
	}

	WeaponInfo->SetSlotColor(false);
	DroneInfo->SetSlotColor(false);
	SpAttackInfo->SetSlotColor(false);
	UltimateInfo->SetSlotColor(false);
}

FReply UTPSInventoryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	WeaponInfo->SetSlotColor(false);
	DroneInfo->SetSlotColor(false);
	SpAttackInfo->SetSlotColor(false);
	UltimateInfo->SetSlotColor(false);

	return FReply::Handled();
}

void UTPSInventoryWidget::OnCloseWindowClicked()
{
	UTPSUiSubsystem* UIsubsystem = GetGameInstance()->GetSubsystem<UTPSUiSubsystem>();
	if (UIsubsystem)
	{
		UIsubsystem->HideCurrentUI();
	}
}

void UTPSInventoryWidget::UpdateEquipmentInfo()
{
	if (WeaponInfo)
	{
		WeaponInfo->InitializeWeaponInfo();
	}

	if (DroneInfo)
	{
		DroneInfo->InitializeDroneInfo();
	}

	if (SpAttackInfo)
	{
		SpAttackInfo->InitializeSpAttackInfo();
	}

	if (UltimateInfo)
	{
		UltimateInfo->InitializeUltimateInfo();
	}
}

void UTPSInventoryWidget::UpdateInventoryInfo()
{
	// Game Instance���� ������ (�����Ƽ, �ؽ�Ʈ, �̹���) �迭�� �ҷ��ͼ� Grid Panel �ڽ����� �߰�
	if (!InventoryGrid)
	{
		return;
	}

	UTPSGameInstance* GI = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());
	if (!GI)
	{
		return;
	}

	InventoryGrid->ClearChildren();
	int32 Index = 0;
	for (UTPSAbilityItem* Item : GI->AbilityInventory)
	{
		if (!Item) continue;

		// InventoryItemWidget ����
		UTPSInventoryItemWidget* ItemWidget = nullptr;

		if (InventoryItemWidgetClass)
		{
			ItemWidget = CreateWidget<UTPSInventoryItemWidget>(this, InventoryItemWidgetClass);
		}

		if (!ItemWidget) continue;

		// HoverWidget ����
		ItemWidget->SetWidgetInfo(Item);
		ItemWidget->OnItemClicked.AddDynamic(this, &UTPSInventoryWidget::HandleItemClicked);

		UGridSlot* GridSlot = InventoryGrid->AddChildToGrid(ItemWidget, Index / 5, Index % 5);
		Index++;
	}
}


void UTPSInventoryWidget::InitializeWidget(ESlateVisibility NewVisibility)
{
	if (NewVisibility != ESlateVisibility::Visible)
	{
		return;
	}

	// ��� ������Ʈ
	UpdateEquipmentInfo();

	// �κ��丮 ������Ʈ
	UpdateInventoryInfo();
}
