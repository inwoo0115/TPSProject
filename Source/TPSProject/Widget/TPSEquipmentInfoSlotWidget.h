// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSEquipmentInfoSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSEquipmentInfoSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	class UImage* SlotImage;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* AbilitySlot;

	class UTPSInventoryItemWidget* Ability;

	void UpdateSlot(class UTPSAbilityItem* Item);

	void SetColor(bool Active);

protected:
	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<class UTPSInventoryItemWidget> InventoryItemWidgetClass;
};
