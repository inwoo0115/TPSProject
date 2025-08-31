// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSInventoryItemWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemClicked, UTPSInventoryItemWidget*, Item);

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UPROPERTY(meta = (BindWidget))
    class UImage* ItemIcon;

    UPROPERTY(meta = (BindWidget))
    class UTPSItemInfoWidget* HoverWidget;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* FadeInAnimation;

    virtual void NativeConstruct() override;

    FVector2D GetWidgetPosition();

    void SetShowTooltip(bool Input);

    void SetWidgetInfo(class UTPSAbilityItem *Item);

    UPROPERTY()
    class UTPSAbilityItem* AbilityItem;

    UPROPERTY(BlueprintAssignable, Category = "Event")
    FOnItemClicked OnItemClicked;

protected:
    virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

    bool bIsHover = false;
    bool bShowTooltip = false;
};
