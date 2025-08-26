// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSInventoryItemWidget.h"
#include "TPSInventoryItemWidget.h"
#include "Components/Widget.h"
#include "Components/CanvasPanelSlot.h"
#include "TPSItemInfoWidget.h" 
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Layout/Geometry.h"             
#include "Components/ScrollBox.h"
#include "Blueprint/SlateBlueprintLibrary.h"

void UTPSInventoryItemWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (HoverWidget)
    {
        if (!HoverWidget->IsInViewport())
        {
            HoverWidget->RemoveFromParent();
            HoverWidget->AddToViewport(20);
        }

        HoverWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

FVector2D UTPSInventoryItemWidget::GetWidgetPosition()
{
    if (!HoverWidget)
    {
        return FVector2D();
    }

    FVector2D MousePosition;
    UWidgetLayoutLibrary::GetMousePositionScaledByDPI(GetOwningPlayer(), MousePosition.X, MousePosition.Y);

    FVector2D ViewportSize;
    GEngine->GameViewport->GetViewportSize(ViewportSize);

    float Scale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());
    ViewportSize /= Scale;

    bool bLeft = MousePosition.X < ViewportSize.X * 0.5f;
    bool bTop = MousePosition.Y < ViewportSize.Y * 0.5f;

    FVector2D WidgetSize = HoverWidget->GetDesiredSize();
    FVector2D NewPos = MousePosition;

    if (bLeft && bTop)
    {
        // ���� ���: �⺻ (���콺 �»�� = ���� �»��)
        NewPos += FVector2D(5.f, 5.f);
    }
    else if (!bLeft && bTop)
    {
        // ������ ���: ���� ���� = ���콺 ��ġ
        NewPos += FVector2D(-WidgetSize.X - 5.f, 5.f);
    }
    else if (bLeft && !bTop)
    {
        // ���� �ϴ�: ���� ���ϴ� = ���콺 ��ġ
        NewPos += FVector2D(5.f, -WidgetSize.Y - 5.f);
    }
    else
    {
        // ������ �ϴ�: ���� ���ϴ� = ���콺 ��ġ
        NewPos += FVector2D(-WidgetSize.X - 5.f, -WidgetSize.Y - 5.f);
    }

    return NewPos;
}

void UTPSInventoryItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

    if (HoverWidget)
    {
        FVector2D NewPos = GetWidgetPosition();

        HoverWidget->SetRenderTranslation(NewPos);

        HoverWidget->SetVisibility(ESlateVisibility::HitTestInvisible);

        bIsHover = true;

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
        bIsHover = false;
        HoverWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

FReply UTPSInventoryItemWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (bIsHover && HoverWidget)
    {
        FVector2D NewPos = GetWidgetPosition();

        HoverWidget->SetRenderTranslation(NewPos);
    }

    return Super::NativeOnMouseMove(InGeometry, InMouseEvent);
}
