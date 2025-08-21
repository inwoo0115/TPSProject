// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSInventoryItemWidget.generated.h"

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
    UWidget* HoverWidget; // 툴팁이나 상세정보 위젯

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* FadeInAnimation;

    virtual void NativeConstruct() override;

protected:
    virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

};
