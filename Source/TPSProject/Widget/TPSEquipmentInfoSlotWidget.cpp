// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSEquipmentInfoSlotWidget.h"
#include "TPSInventoryItemWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"

void UTPSEquipmentInfoSlotWidget::UpdateSlot(UTPSAbilityItem* Item)
{
    Ability = CreateWidget<UTPSInventoryItemWidget>(this, InventoryItemWidgetClass);
    Ability->SetWidgetInfo(Item);
    AbilitySlot->AddChild(Ability);
}

void UTPSEquipmentInfoSlotWidget::SetColor(bool Active)
{
    if (Active)
    {
        SlotImage->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
    }
    else
    {
        SlotImage->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.3f));
    }
}

FReply UTPSEquipmentInfoSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    if (OnSlotClicked.IsBound())
    {
        OnSlotClicked.Broadcast(this);
    }

    return FReply::Handled();
}
