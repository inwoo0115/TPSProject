// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTPSEquipmentInfoWidget* WeaponInfo;

	UPROPERTY(meta = (BindWidget))
	class UTPSEquipmentInfoWidget* SpAttackInfo;

	UPROPERTY(meta = (BindWidget))
	class UTPSEquipmentInfoWidget* UltimateInfo;

	UPROPERTY(meta = (BindWidget))
	class UTPSEquipmentInfoWidget* DroneInfo;

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* InventoryGrid;

	UPROPERTY(meta = (BindWidget))
	class UButton* CloseWindowButton;

	UFUNCTION()
	void OnCloseWindowClicked();

	UFUNCTION()
	void UpdateEquipmentInfo();

	UFUNCTION()
	void UpdateInventoryInfo();

	UFUNCTION()
	void InitializeWidget(ESlateVisibility NewVisibility);

	UFUNCTION()
	void AddInventoryInfo(class UTPSAbilityItem* Item);

	UFUNCTION()
	void HandleItemRightClicked(class UTPSInventoryItemWidget* Item);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<class UTPSInventoryItemWidget> InventoryItemWidgetClass;

	UFUNCTION()
	void HandleItemLeftClicked(class UTPSInventoryItemWidget* Item); 

	UFUNCTION()
	void HandleSlotClicked(class UTPSEquipmentInfoSlotWidget* SlotWidget);

	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY()
	UTPSInventoryItemWidget* PendingItem;

};
