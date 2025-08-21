// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSInventoryItemWidget.h"
#include "TPSInventoryItemWidget.h"
#include "Components/Widget.h"
#include "Components/CanvasPanelSlot.h"
#include "TPSItemInfoWidget.h" 

void UTPSInventoryItemWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (HoverWidget)
    {
        HoverWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UTPSInventoryItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

    if (HoverWidget)
    {
        HoverWidget->SetVisibility(ESlateVisibility::Visible);

        if (FadeInAnimation)
        {
            PlayAnimation(FadeInAnimation);
        }
    }
}

void UTPSInventoryItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);

    if (HoverWidget)
    {
        HoverWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}
