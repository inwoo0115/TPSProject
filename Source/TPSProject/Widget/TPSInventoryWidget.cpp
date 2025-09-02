// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSInventoryWidget.h"
#include "Components/Button.h"
#include "Character/TPSCharacterBase.h"
#include "TPSEquipmentInfoWidget.h"
#include "Gameinstance/TPSUiSubsystem.h"
#include "GameInstance/TPSGameInstance.h"
#include "Components/WrapBox.h"
#include "Components/WrapBoxSlot.h"
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

void UTPSInventoryWidget::HandleItemLeftClicked(UTPSInventoryItemWidget* Item)
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

void UTPSInventoryWidget::HandleItemRightClicked(UTPSInventoryItemWidget* Item)
{
	if (!PendingItem && Item->GetIsEquipped())
	{
		AddInventoryInfo(Item->AbilityItem);
		Item->HoverWidget->SetVisibility(ESlateVisibility::Hidden);
		Item->RemoveFromParent();
	}
}

void UTPSInventoryWidget::HandleSlotClicked(UTPSEquipmentInfoSlotWidget* SlotWidget)
{
	if (PendingItem && !SlotWidget->Ability && SlotWidget->SlotType == PendingItem->AbilityItem->GetAbilityType())
	{
		SlotWidget->UpdateSlot(PendingItem->AbilityItem, this);
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

	PendingItem = nullptr;

	return FReply::Handled();
}

void UTPSInventoryWidget::OnCloseWindowClicked()
{
	// UI 제거
	UTPSUiSubsystem* UIsubsystem = GetGameInstance()->GetSubsystem<UTPSUiSubsystem>();
	if (UIsubsystem)
	{
		UIsubsystem->HideCurrentUI();
	}

	// Game Instance에 인벤토리 정보 업데이트
	UTPSGameInstance* GameInstance = Cast<UTPSGameInstance>(GetGameInstance());
	if (!GameInstance) return;

	GameInstance->ResetInventory();

	// 인벤토리 업데이트
	if (InventoryGrid)
	{
		for (UWidget* Child : InventoryGrid->GetAllChildren())
		{
			if (UTPSInventoryItemWidget* ItemWidget = Cast<UTPSInventoryItemWidget>(Child))
			{
				UTPSAbilityItem* NewCopy = DuplicateObject<UTPSAbilityItem>(ItemWidget->AbilityItem, this);
				GameInstance->AbilityInventory.Add(NewCopy);
			}
		}
	}

	if (WeaponInfo)
	{
		WeaponInfo->UpdateWeaponInfoData();
	}
	if (DroneInfo)
	{
		DroneInfo->UpdateDroneInfoData();
	}
	if (SpAttackInfo)
	{
		SpAttackInfo->UpdateSpAttackInfoData();
	}
	if (UltimateInfo)
	{
		UltimateInfo->UpdateUltimateInfoData();
	}
}

void UTPSInventoryWidget::UpdateEquipmentInfo()
{
	if (WeaponInfo)
	{
		WeaponInfo->InitializeWeaponInfo(this);
	}

	if (DroneInfo)
	{
		DroneInfo->InitializeDroneInfo(this);
	}

	if (SpAttackInfo)
	{
		SpAttackInfo->InitializeSpAttackInfo(this);
	}

	if (UltimateInfo)
	{
		UltimateInfo->InitializeUltimateInfo(this);
	}
}

void UTPSInventoryWidget::UpdateInventoryInfo()
{
	// Game Instance에서 아이템 (어빌리티, 텍스트, 이미지) 배열을 불러와서 Grid Panel 자식으로 추가
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

		AddInventoryInfo(Item);
		Index++;
	}
}


void UTPSInventoryWidget::InitializeWidget(ESlateVisibility NewVisibility)
{
	if (NewVisibility != ESlateVisibility::Visible)
	{
		return;
	}

	// 장비 업데이트
	UpdateEquipmentInfo();

	// 인벤토리 업데이트
	UpdateInventoryInfo();
}

void UTPSInventoryWidget::AddInventoryInfo(UTPSAbilityItem* Item)
{
	// InventoryItemWidget 생성
	UTPSInventoryItemWidget* ItemWidget = nullptr;

	if (InventoryItemWidgetClass)
	{
		ItemWidget = CreateWidget<UTPSInventoryItemWidget>(this, InventoryItemWidgetClass);
	}
	if (!ItemWidget) return;

	// HoverWidget 세팅
	ItemWidget->SetWidgetInfo(Item);
	ItemWidget->OnItemClicked.AddDynamic(this, &UTPSInventoryWidget::HandleItemLeftClicked);
	InventoryGrid->AddChildToWrapBox(ItemWidget);
}
