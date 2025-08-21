// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSInventoryItemWidget.h"
#include "TPSInventoryItemWidget.h"
#include "Components/Widget.h"
#include "Components/CanvasPanelSlot.h"

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
        HoverWidget->SetRenderTranslation(InMouseEvent.GetScreenSpacePosition());
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

FReply UTPSInventoryItemWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseMove(InGeometry, InMouseEvent);

    if (HoverWidget)
    {
        // CanvasPanelSlot이 있어야 위치 변경 가능
        if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(HoverWidget->Slot))
        {
            FVector2D MousePos = InMouseEvent.GetScreenSpacePosition();
            CanvasSlot->SetPosition(MousePos + FVector2D(10.f, 10.f)); // 마우스 커서 + 오프셋
        }
    }

    return Reply;
}
