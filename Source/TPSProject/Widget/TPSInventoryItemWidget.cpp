// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSInventoryItemWidget.h"
#include "TPSInventoryItemWidget.h"
#include "Components/Widget.h"
#include "Components/CanvasPanelSlot.h"
#include "TPSItemInfoWidget.h" 
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Layout/Geometry.h"             
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Item/TPSAbilityItem.h"


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
        // 왼쪽 상단: 기본 (마우스 좌상단 = 위젯 좌상단)
        NewPos += FVector2D(5.f, 5.f);
    }
    else if (!bLeft && bTop)
    {
        // 오른쪽 상단: 위젯 우상단 = 마우스 위치
        NewPos += FVector2D(-WidgetSize.X - 5.f, 5.f);
    }
    else if (bLeft && !bTop)
    {
        // 왼쪽 하단: 위젯 좌하단 = 마우스 위치
        NewPos += FVector2D(5.f, -WidgetSize.Y - 5.f);
    }
    else
    {
        // 오른쪽 하단: 위젯 우하단 = 마우스 위치
        NewPos += FVector2D(-WidgetSize.X - 5.f, -WidgetSize.Y - 5.f);
    }
    
    return NewPos;
}

void UTPSInventoryItemWidget::SetShowTooltip(bool Input)
{
    bShowTooltip = Input;
}

void UTPSInventoryItemWidget::SetIsEquipped(bool Equipped)
{
    bIsEquipped = Equipped;
}

bool UTPSInventoryItemWidget::GetIsEquipped()
{
    return bIsEquipped;
}

void UTPSInventoryItemWidget::SetWidgetInfo(UTPSAbilityItem* Item)
{
    HoverWidget->ItemNameText->SetText(Item->GetAbilityNameText());
    HoverWidget->ItemInfoText->SetText(Item->GetAbilityDescriptionText());
    HoverWidget->ItemIcon->SetBrushFromTexture(Item->GetItemImage());
    ItemIcon->SetBrushFromTexture(Item->GetItemImage());
    AbilityItem = DuplicateObject<UTPSAbilityItem>(Item, GetTransientPackage());
    SetShowTooltip(true);
}

void UTPSInventoryItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

    if (HoverWidget && bShowTooltip)
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

    if (HoverWidget && bShowTooltip)
    {
        bIsHover = false;
        HoverWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

FReply UTPSInventoryItemWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (bIsHover && HoverWidget && bShowTooltip)
    {
        FVector2D NewPos = GetWidgetPosition();

        HoverWidget->SetRenderTranslation(NewPos);
    }

    return Super::NativeOnMouseMove(InGeometry, InMouseEvent);
}

FReply UTPSInventoryItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);


    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        if (OnItemClicked.IsBound())
        {
            OnItemClicked.Broadcast(this);
        }
    }
    else if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
    {
        if (OnEquippedItemClicked.IsBound())
        {
            OnEquippedItemClicked.Broadcast(this);
        }
    }

    return FReply::Handled();
}
