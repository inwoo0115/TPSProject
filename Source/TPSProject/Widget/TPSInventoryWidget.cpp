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

void UTPSInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseWindowButton)
		CloseWindowButton->OnClicked.AddDynamic(this, &UTPSInventoryWidget::OnCloseWindowClicked);

	OnVisibilityChanged.AddDynamic(this, &UTPSInventoryWidget::InitializeWidget);

}

FReply UTPSInventoryWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
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

void UTPSInventoryWidget::OnCloseWindowClicked()
{
	auto UIsubsystem = GetGameInstance()->GetSubsystem<UTPSUiSubsystem>();
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

		// InventoryItemWidget 생성
		UTPSInventoryItemWidget* ItemWidget = nullptr;

		if (InventoryItemWidgetClass)
		{
			ItemWidget = CreateWidget<UTPSInventoryItemWidget>(this, InventoryItemWidgetClass);
		}

		if (!ItemWidget) continue;

		// HoverWidget 세팅
		if (ItemWidget->HoverWidget)
		{
			ItemWidget->HoverWidget->ItemNameText->SetText(Item->GetAbilityNameText());
			ItemWidget->HoverWidget->ItemInfoText->SetText(Item->GetAbilityDescriptionText());
		}

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

	// 장비 업데이트
	UpdateEquipmentInfo();

	// 인벤토리 업데이트
	UpdateInventoryInfo();
}
